/**
 *  @file	TapascoStatusScreen.hpp
 *  @brief	Kernel map screen for tapasco-debug.
 *  @author	J. Korinth, TU Darmstadt (jk@esa.cs.tu-darmstadt.de)
 **/
#ifndef TAPASCO_STATUS_SCREEN_HPP__
#define TAPASCO_STATUS_SCREEN_HPP__

#include <tapasco.hpp>
extern "C" {
  #include <tapasco.h>
  #include <tapasco_device_info.h>
}
#include <cstring>
#include <ctime>
#include "MenuScreen.hpp"
using namespace tapasco;

class TapascoStatusScreen: public MenuScreen {
public:
  TapascoStatusScreen(Tapasco *tapasco): MenuScreen("", vector<string>()), tapasco(*tapasco) {
    delay_us = 10000;
  }
  virtual ~TapascoStatusScreen() {}
protected:
  virtual void render() {
    const int col_d = 20;
    int start_c = (cols - 4 * col_d) / 2;
    int start_r = (rows - 6 - 32) / 2;
    const string t = "Current Bitstream Kernel Map (via TaPaSCo Status Core)";
    mvprintw(start_r, (cols - t.length()) / 2, t.c_str());
    for (int col = 0; col < 4; ++col) {
      for (int row = 0; row < 32; ++row) {
        attron(A_REVERSE);
	mvprintw(start_r + 2 + row, start_c + col * col_d, "%03d:", col * 32 + row);
	attroff(A_REVERSE);
        if (info.kernel_id[col * 32 + row])
          mvprintw(start_r + 2 + row, start_c + 4 + col * col_d, " 0x%08x", info.kernel_id[col * 32 + row]);
	else
          mvprintw(start_r + 2 + row, start_c + 4 + col * col_d, "           ", col * 32 + row);
      }
    }
    attron(A_REVERSE);
    mvhline(start_r + 34, (cols - 80) / 2, ' ', 80);
    mvhline(start_r + 35, (cols - 80) / 2, ' ', 80);
    mvprintw(start_r + 34, (cols - 80) / 2, "#intc: % 2u vivado: %s tapasco: %s gen_ts: %s",
        info.num_intc, vivado_str, tapasco_str, gen_ts_str);
    mvprintw(start_r + 35, (cols - 80) / 2, "host clk: %3d MHz mem clk: %3d MHz design clk: %3d MHz, caps0: 0x%08x",
        info.clock.host, info.clock.memory, info.clock.design, info.caps0);
    attroff(A_REVERSE);
    mvprintw(start_r + 36, (cols - text_press_key.length()) / 2, text_press_key.c_str());
  }

  virtual void update() {
    memset(&info, 0, sizeof(info));
    tapasco_device_info(tapasco.device(), &info);
    snprintf(vivado_str, sizeof(vivado_str), "%4d.%1d",
    		TAPASCO_VERSION_MAJOR(info.vivado_version),
		TAPASCO_VERSION_MINOR(info.vivado_version));
    snprintf(tapasco_str, sizeof(tapasco_str), "%4d.%1d",
    		TAPASCO_VERSION_MAJOR(info.tapasco_version),
		TAPASCO_VERSION_MINOR(info.tapasco_version));
  }

  virtual int perform(const int choice) {
    if (choice == ERR) delay();
    return choice;
  }

private:
  Tapasco &tapasco;
  tapasco_device_info_t info;
  char     vivado_str[16];
  char     tapasco_str[16];
  char     gen_ts_str[64];
  const string text_press_key { "--- press any key to exit ---" };
};

#endif /* TAPASCO_STATUS_SCREEN_HPP__ */
/* vim: set foldmarker=@{,@} foldlevel=0 foldmethod=marker : */
