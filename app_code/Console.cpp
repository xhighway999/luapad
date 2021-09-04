#include "Console.hpp"
Console::Console() {
  setTitle("Console");
}

void Console::onDraw() {


    if (firstFrame) {
        firstFrame = false;
        initState();
    }

    float iconSize = ImGui::GetFrameHeight();
    if (ImGui::ImageButton(trashImg.textureID(), ImVec2(iconSize, iconSize),
                           ImVec2(), ImVec2(1, 1), 0)) {
      consoleBuffer.clear();
    }

  auto footer_height_to_reserve =
      ImGui::GetTextLineHeight() + ImGui::GetStyle().ItemSpacing.y;

  static std::string inputLine;
  ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve * 2),
                    true, ImGuiWindowFlags_HorizontalScrollbar);

  ImGui::TextUnformatted(consoleBuffer.c_str());
  if (lineChange) {
    ImGui::SetScrollHereY(1);
    lineChange = false;
  }
  ImGui::EndChild();

  bool changeHist = false;
  if (ImGui::IsKeyPressed(XHFR_KEY(UP))) {
    changeHist = true;
    historyPos = std::min<unsigned>(history.size() - 1, historyPos + 1);
  }
  if (ImGui::IsKeyPressed(XHFR_KEY(DOWN))) {
    changeHist = true;
    if (historyPos != 0)
      historyPos--;
  }
  if (changeHist) {
    inputLine = getHistory();
  }
  static std::string multilineBuffer = "";
  if (ImGui::InputText("##line", inputLine,
                       ImGuiInputTextFlags_EnterReturnsTrue)) {
    if (inputLine.back() == '\\') {
      addLineToConsole("> " + inputLine);
      inputLine.back() = '\n';
      multilineBuffer += inputLine;
      inputLine = "";
      return;
    }
    multilineBuffer += inputLine;
    std::string commandToExecute = multilineBuffer;
    multilineBuffer = "";
    try {
      ImGui::SetKeyboardFocusHere();
      // If we have an assigment we cannot print the result
      //(*state)["print_orig"] = (*state)["print"];
      //(*state)["print"] = (*state)["print_replacement"];
      if (isImmediate(commandToExecute)) {
        state->script(commandToExecute);
      } else {
        state->script("print(" + commandToExecute + ")");
      }

    } catch (const std::exception& e) {
      // print errors to screen
      addLineToConsole(e.what());
    }
    //(*state)["print"] = (*state)["print_orig"];
    // clear input
    inputLine = "";
  };
}

bool Console::isImmediate(const std::string& line) {
  for (const auto& up : unprintable) {
    if (line.find(up) != std::string::npos) {
      return true;
    }
  }
  return false;
}

void Console::addTextToConsole(const std::string &text)
{
    consoleBuffer += text;
    lineChange = true;
}

const std::string& Console::getHistory() {
  return history[std::min(history.size(), historyPos)];
}

void Console::addLineToConsole(const std::string& line) {
  consoleBuffer += line + '\n';
  lineChange = true;
}

void Console::initState()
{

    (*state)["console_print"] = [this](const std::string& line) {
      addLineToConsole(line);
    };

    (*state)["console_puts"] = [this](const std::string& line) {
      addTextToConsole(line);
    };

    auto consolePrintScript =
        "function print_replacement(x)\n"
        "if  x ~= nil then\n"
        "    console_puts(tostring(x))\n"
        "else\n"
        "   console_puts(\'nil\')\n"
        "end\n"
        "end\n"
        "print = print_replacement\n";


    auto consoleMultiPrint = R"(

function multi_print(...)

for i = 1, select('#', ...) do
    console_puts(tostring(select(i, ...)))
    console_puts("\t")
end
console_puts("\n")
end
print = multi_print

    )";

    (*state).script(consolePrintScript);

    (*state).script(consoleMultiPrint);
}

