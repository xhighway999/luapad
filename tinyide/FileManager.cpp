#include "FileManager.hpp"

FileManager::MenuEntry e = {{"Open in Termainl"},
                            {xhfr::fs::Regular},
                            {[](const xhfr::fs::FileInfo& info) {}}};
FileManager::MenuEntry delFile = {
    "Delete", xhfr::fs::Regular,
    [](const xhfr::fs::FileInfo& info) { xhfr::fs::deleteFile(info.path); }};
std::vector<FileManager::MenuEntry> FileManager::menuOptions = {delFile};

FileManager::FileManager(FileManagerType fileManagerType) {
  currentFileManagerType = fileManagerType;
  setTitle("File Manager");
  update();
}

void FileManager::onDraw() {
  // bookmarks bar here
  {
    ImGui::BeginChild("##bookmarkssplit", ImVec2(150, 0));
    ImGui::EndChild();
  }
  ImGui::SameLine();

  // all the other stuff
  {
    ImGui::BeginChild("##mainframe");
    optionsMenu();
    if (showMountMenu) {
      mountpointsMenu();
    }

    float iconSize = ImGui::GetFrameHeight();
    if (ImGui::ImageButton(reload.textureID(), ImVec2(iconSize, iconSize),
                           ImVec2(), ImVec2(1, 1), 0)) {
      update();
    }
    ImGui::SameLine();
    if (ImGui::Button("Touch file")) {
      ImGui::OpenPopup("TouchFile");
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(createFolder.textureID(), ImVec2(iconSize, iconSize),
                           ImVec2(), ImVec2(1, 1), 0)) {
      ImGui::OpenPopup("CreateFolder");
    }
    ImGui::SameLine();

    if (ImGui::BeginPopup("TouchFile")) {
      static std::string fileName;
      ImGui::InputText("File Name", fileName);
      if (ImGui::Button("Create")) {
        xhfr::File f(currentPath + fileName, true);
        f.close();
        ImGui::CloseCurrentPopup();
        update();
      }
      ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("CreateFolder")) {
      static std::string fileName;
      ImGui::InputText("Folder Name", fileName);
      if (ImGui::Button("Create")) {
        xhfr::fs::createDirectory(currentPath + fileName);
        ImGui::CloseCurrentPopup();
        update();
      }
      ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("AddArchive")) {
      static std::string archiveName, mountPoint;
      ImGui::InputText("Archive Name", archiveName);
      ImGui::InputText("Mount Point", mountPoint);
      if (ImGui::Button("Create")) {
        PHYSFS_mount(archiveName.c_str(), mountPoint.c_str(), 0);
      }
      ImGui::EndPopup();
    }

    {
      static size_t i = 0;

      if (ImGui::ImageButton(chevronUpImg.textureID(),
                             ImVec2(iconSize, iconSize), ImVec2(), ImVec2(1, 1),
                             0)) {
        std::string newPath;
        if (currentPath.size() != 1) {
          size_t i;
          for (i = currentPath.size() - 2; i != 0; i--) {
            if (currentPath[i] == '/') {
              currentPath = currentPath.substr(0, i + 1);
              update();
              break;
            }
          }
          if (i == 0) {
            currentPath.resize(1);
            update();
          }
        }
      }

      ImGui::SameLine();
      if (ImGui::InputText("##FilePath", currentPath,
                           ImGuiInputTextFlags_EnterReturnsTrue)) {
        update();
      }

      ImGui::BeginChild("FILES", ImVec2(0, 200));
      ImGui::Columns(3);
      ImGui::Text("Filename");
      ImGui::NextColumn();
      ImGui::Text("Type");
      ImGui::NextColumn();
      ImGui::Text("Size");
      // ImGui::NextColumn();
      ImGui::Separator();
      ImGui::Columns();

      ImGui::BeginChild("FILESSCROLL", ImVec2(0, 0), true);
      ImGui::Columns(3);

      const char* fileTypes[] = {"Regular", "Folder", "Symlink", "Other"};

      for (size_t var = 0; var < filesInDir.size(); ++var) {
        auto& m = filesInDir[var];
        char label[128];
        sprintf(label, "%s", m.name.c_str());
        if (m.type == xhfr::fs::Directory) {
          ImGui::Image(folder.textureID(), ImVec2(ImGui::GetTextLineHeight(),
                                                  ImGui::GetTextLineHeight()));
          ImGui::SameLine();
        }
        if (ImGui::Selectable(label, filesSelected[var],
                              ImGuiSelectableFlags_SpanAllColumns |
                                  ImGuiSelectableFlags_AllowDoubleClick)) {
          if (ImGui::IsMouseDoubleClicked(0)) {
            if (m.type == xhfr::fs::Directory) {
              currentPath += (m.name + "/");
              update();
            }
          } else {
            filesSelected[var] = !filesSelected[var];
          }
        }
        if (ImGui::IsItemClicked(1)) {
          ImGui::OpenPopup("RMenu");
          i = var;
        }
        if (m.readonly) {
          ImGui::SameLine();
          float lh = ImGui::GetTextLineHeight();
          ImGui::Image(lock.textureID(), ImVec2(lh, lh), ImVec2(),
                       ImVec2(1, 1));
        }

        ImGui::NextColumn();
        ImGui::Text("%s", fileTypes[m.type]);
        ImGui::NextColumn();
        // 1KB = 1024B. Change my mind
        ImGui::Text("%.6f KB", (double)m.size / 1024.f);
        ImGui::NextColumn();
      }
      ImGui::EndChild();

      if (ImGui::BeginPopup("RMenu")) {
        for (auto& testMenuEntry : menuOptions) {
          if (testMenuEntry.shouldShowOption(filesInDir[i])) {
            if (ImGui::MenuItem(testMenuEntry.optionName.c_str())) {
              testMenuEntry.callback(filesInDir[i]);
              update();
              ImGui::CloseCurrentPopup();
              break;
            }
          }
        }
        ImGui::EndPopup();
      }
      ImGui::EndChild();
    }
    fileManagerType();
    ImGui::EndChild();
  }
}

std::vector<xhfr::fs::FileInfo> FileManager::getSelectedFiles() {
  if (newFileName.size() != 0) {
    xhfr::fs::FileInfo fi;
    fi.name = newFileName;
    fi.size = 0;
    fi.readonly = false;
    fi.path = currentPath;
    if (fi.path.back() != '/') {
      fi.path += '/';
    }
    fi.path += newFileName;
    return {fi};
  }

  std::vector<xhfr::fs::FileInfo> entries;
  assert(filesSelected.size() == filesInDir.size());
  for (size_t i = 0; i < filesSelected.size(); ++i) {
    if (filesSelected[i]) {
      entries.push_back(filesInDir[i]);
    }
  }
  return entries;
}

void FileManager::setOnOkAction(std::function<void()> action) {
  onOkayAction = action;
}

void FileManager::setOnFileClickedAction(std::function<void()> action) {
  fileClickedAction = action;
}

void FileManager::update() {
  if (xhfr::fs::exists(currentPath)) {
    filesInDir = xhfr::fs::listFiles(currentPath.c_str());
    filesSelected.resize(0);
    filesSelected.resize(filesInDir.size(), false);
  }
}

void FileManager::optionsMenu() {
  auto& io = ImGui::GetIO();

  if (io.KeyAlt && ImGui::IsKeyPressed(XHFR_KEY(ENTER))) {
    showToolbar = !showToolbar;
    setFlag(ImGuiWindowFlags_MenuBar, showToolbar);
  }
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("Options")) {
      if (ImGui::MenuItem("Show Mountpoint Menu", NULL, &showMountMenu)) {
        // showMountMenu = !showMountMenu;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

void FileManager::mountpointsMenu() {
  if (ImGui::Button("Add Archive")) {
    ImGui::OpenPopup("AddArchive");
  }

  struct Mapping {
    std::string realDir, mountPoint;
  };

  static std::vector<Mapping> mountPoints;

  if (ImGui::Button("Update Mounts")) {
    mountPoints.resize(0);
    for (char** i = PHYSFS_getSearchPath(); *i != NULL; i++) {
      const char* realPath = *i;
      const char* mountPoint = PHYSFS_getMountPoint(realPath);
      mountPoints.push_back(Mapping{realPath, mountPoint});
    }
  }

  {
    ImGui::BeginChild("MOUNTS", ImVec2(0, 200));

    if (ImGui::BeginChild("MOUNTPOINTS", ImVec2(0, 200), true)) {
      ImGui::Columns(2);
      ImGui::Text("real path");
      ImGui::NextColumn();
      ImGui::Text("mountpoint");
      ImGui::NextColumn();

      for (size_t var = 0; var < mountPoints.size(); ++var) {
        auto& m = mountPoints[var];
        ImGui::Text("%s", m.realDir.c_str());
        ImGui::NextColumn();
        ImGui::Text("%s", m.mountPoint.c_str());
        ImGui::NextColumn();
      }

      ImGui::EndChild();
    }

    ImGui::EndChild();
  }
}

void FileManager::fileManagerType() {
  if (currentFileManagerType == None) {
    return;
  }
  bool textfieldReturn = false;
  if (currentFileManagerType == Create) {
    ImGui::Text("Filename");
    ImGui::SameLine();
    textfieldReturn = ImGui::InputText("##Filename", newFileName,
                                       ImGuiInputTextFlags_EnterReturnsTrue);
  }

  if (ImGui::Button("OK", ImVec2(50, 0)) | textfieldReturn) {
    if (getSelectedFiles().size() != 0 || newFileName.size() != 0) {
      onOkayAction();
      setVisible(false);
      destroy();
    } else {
      ImGui::OpenPopup("SelectFile");
    }
  }

  if (ImGui::BeginPopup("SelectFile")) {
    if (currentFileManagerType == Create) {
      ImGui::Text("Select or create a file");
    } else {
      ImGui::Text("Select a file");
    }
    if (ImGui::Button("OK")) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }

  ImGui::SameLine();
  if (ImGui::Button("Cancel", ImVec2(50, 0))) {
    setVisible(false);
    destroy();
  }
}

void FileManager::bookmarks() {}

bool FileManager::MenuEntry::shouldShowOption(const xhfr::fs::FileInfo info) {
  return true;
}
