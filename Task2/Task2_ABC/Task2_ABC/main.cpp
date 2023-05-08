#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#if _WIN32
#include <windows.h>
#endif

using namespace std;

class Screen {
public:
  Screen() {
#ifdef _WIN32
    _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    hideCursor();
    saveCursorPosition();
  }

  void clear() {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        _screen[i][j] = 'x';
      }
    }
  }

  void draw(char value, float x, float y) {
    int xPos = lround(x);
    int yPos = lround(y);
    if (xPos < width && yPos < height) {
      _screen[yPos][xPos] = value;
    }
  }

  void flush() {
    restoreCursorPosition();

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (_screen[i][j] != 'x') {
          setRedFont();
        } else {
          setWhiteFont();
        }
        cout << _screen[i][j];
      }
      cout << "\n";
    }
  }

private:
  void hideCursor() {
#ifdef _WIN32
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(_hConsole, &cursorInfo);
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(_hConsole, &cursorInfo);
#else
    cout << "\33[?25l"; // disable cursor
#endif
  }

  void saveCursorPosition() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(_hConsole, &coninfo);
    _prevPos = coninfo.dwCursorPosition;
#else
    cout << "\33[s";
#endif
  }

  void restoreCursorPosition() {
#ifdef _WIN32
    SetConsoleCursorPosition(_hConsole, _prevPos);
#else
    cout << "\338";
#endif
  }

  void setRedFont() {
#ifdef _WIN32
    WORD attributes = FOREGROUND_RED;
    SetConsoleTextAttribute(_hConsole, attributes);
#else
    cout << "\33[31m"; // red color
#endif
  }

  void setWhiteFont() {
#ifdef _WIN32
    WORD attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    SetConsoleTextAttribute(_hConsole, attributes);
#else
    cout << "\33[37m"; // white color
#endif
  }

  static constexpr int width{60};
  static constexpr int height{20};
  char _screen[height][width];
#ifdef _WIN32
  HANDLE _hConsole;
  COORD _prevPos;
#endif
};

struct Position {
  float x;
  float y;
};

using Pixel = char;

class Engine {
public:
  void update(chrono::milliseconds deltaTime) {
    // Update time since the start
    time += deltaTime;
    // Update elapsed time since last point was reached
    elapsed_time += deltaTime;

    // Move pixel from A to B in 2000ms
    if (elapsed_time <= 2000ms) {
      float progress = static_cast<float>(elapsed_time.count()) / 2000.0f;
      position.x = linInterpolation(0.0f, 40.0f, progress);
      position.y = 0.0f;
    }
    // Move pixel from B to C in 3000ms
    else if (elapsed_time <= 5000ms) {
      float progress =
          static_cast<float>(elapsed_time.count() - 2000) / 3000.0f;
      position.x = 40.0f;
      position.y = linInterpolation(0.0f, 10.0f, progress);
    }
    // Move pixel from C to A in 1000ms
    else if (elapsed_time <= 6005ms) {
      float progress =
          static_cast<float>(elapsed_time.count() - 5000) / 1000.0f;
      position.x = linInterpolation(40.0f, 0.0f, progress);
      position.y = linInterpolation(10.0f, 0.0f, progress);
    } else {
      elapsed_time = 0ms;
      cycle_count++;
      position.x = 0.0f;
      position.y = 0.0f;
    }
  }

  void render(Screen &screen) const {
    screen.draw(pixel, position.x, position.y);
  }

  Position getPosition() const { return position; }
  long long getTime() const { return time.count(); }

  int getCycleCount() { return cycle_count; }

private:
  Pixel pixel{1};
  Position position{0.0f, 0.0f};
  chrono::milliseconds elapsed_time{0ms};
  chrono::milliseconds time{};
  int cycle_count{0};

  // Linear interpolation function
  float linInterpolation(float source, float destination, float t) const {
    return floor((1.0f - t) * source + t * destination);
  }
};

int main() {
  Engine engine;
  Screen screen;
  const int MAX_CYCLE_COUNT = 5;

  auto startTime = chrono::high_resolution_clock::now();
  while (1) {
    
    auto now = chrono::high_resolution_clock::now();
    auto deltaTime =
        chrono::duration_cast<chrono::milliseconds>(now - startTime);
    if (deltaTime >= 20ms) {
      screen.clear();
      cout << "X: " << setw(2) << setfill(' ') << engine.getPosition().x
           << setw(2) << setfill(' ') << " Y: " << engine.getPosition().y
           << '\n';
      cout << (float)engine.getTime() / 1000.0f << " s";

      // Stop the program after 5 cycles
      if (engine.getCycleCount() >= MAX_CYCLE_COUNT) {
          break;
      }

      engine.update(deltaTime);
      engine.render(screen);
      screen.flush();
      startTime = now;
    }
  }
  return 0;
}
