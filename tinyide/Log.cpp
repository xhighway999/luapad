#include "Log.hpp"

Log::Log() {
  setTitle("Log");
}

void Log::addLogEntry(const std::string& str) {
  logMessages.push_back(str);
}

void Log::onDraw() {
  ImGui::BeginChild("ScrollFrame");
  ImGuiListClipper clipper(logMessages.size());
  while (clipper.Step()) {
    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd;
         ++line_no) {
      ImGui::TextUnformatted(logMessages[line_no].c_str());
    }
  }
  ImGui::EndChild();
}
