/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Chinese
 *
 * LCD Menu Messages
 * See also http://marlinfw.org/docs/development/lcd_language.html
 *
 */
#ifndef LANGUAGE_CN_H
#define LANGUAGE_CN_H

#define DISPLAY_CHARSET_ISO10646_CN
#define CHARSIZE 3
#define MAPPER_HASHCN


#define WELCOME_MSG                         "\xa4\xa5\xa6\xa7"
#define MSG_SD_INSERTED                     "\xa8\xa9\xaa\xab"
#define MSG_SD_REMOVED                      "\xa8\xa9\xac\xad"
#define MSG_MAIN                            "\xae\xaf\xb0"
#define MSG_AUTOSTART                       "\xb1\xb2\xb3\xb4"
#define MSG_DISABLE_STEPPERS                "\xb5\xb6\xb7\xb8\xb9\xba"
#define MSG_AUTO_HOME                       "\xbb\xbc\xbd"
#define MSG_AUTO_HOME_X                     "\xbbX\xbc\xbd"
#define MSG_AUTO_HOME_Y                     "\xbbY\xbc\xbd"
#define MSG_AUTO_HOME_Z                     "\xbbZ\xbc\xbd"
#define MSG_TMC_Z_CALIBRATION               "\x7f\xa4 Z"
#define MSG_LEVEL_BED_HOMING                "\xc4\xc7XYZ\xbb\xbc\xbd\x9b..."
#define MSG_LEVEL_BED_WAITING               "\xbd\x99\xb3\xb4\xc4\xc7\xcf\xd0"
#define MSG_LEVEL_BED_DONE                  "\xa9\xcf\xd0!"
#define MSG_SET_HOME_OFFSETS                "\xbe\xbf\xbb\xbc\xbd\xc0\xc1"
#define MSG_HOME_OFFSETS_APPLIED            "\xc0\xc1\xa9\xb3\x9a"
#define MSG_SET_ORIGIN                      "\xbe\xbf\xbc\xbd"
#define MSG_PREHEAT_1                       "\xc3\xc4 PLA"
#define MSG_PREHEAT_1_N                     MSG_PREHEAT_1 " "
#define MSG_PREHEAT_1_ALL                   MSG_PREHEAT_1 " \xc5\xc6"
#define MSG_PREHEAT_1_END					MSG_PREHEAT_1 " \xd3\xd4"
#define MSG_PREHEAT_1_BEDONLY               MSG_PREHEAT_1 " \xc4\xc7"
#define MSG_PREHEAT_1_SETTINGS              MSG_PREHEAT_1 " \xbe\xbf"
#define MSG_PREHEAT_2                       "\xc3\xc4 ABS"
#define MSG_PREHEAT_2_N                     MSG_PREHEAT_2 " "
#define MSG_PREHEAT_2_ALL                   MSG_PREHEAT_2 " \xc5\xc6"
#define MSG_PREHEAT_2_END					MSG_PREHEAT_2 " \xd3\xd4"
#define MSG_PREHEAT_2_BEDONLY               MSG_PREHEAT_2 " \xbe\xc6"
#define MSG_PREHEAT_2_SETTINGS              MSG_PREHEAT_2 " \xbe\xbf"
#define MSG_COOLDOWN                        "\xc8\xc9"
#define MSG_SWITCH_PS_ON                    "\xb9\xcb\xca\xb3"
#define MSG_SWITCH_PS_OFF                   "\xb9\xcb\xb5\xb6"
#define MSG_EXTRUDE                         "\xcc\xad"
#define MSG_RETRACT                         "\xbb\xcd"
#define MSG_MOVE_AXIS                       "\xc1\xb2\xce"
#define MSG_BED_LEVELING                    "\xcf\xd0\xc4\xc7"
#define MSG_LEVEL_BED                       "\xcf\xd0\xc4\xc7"
#define MSG_MOVE_X                          "\xc1\xb2 X"
#define MSG_MOVE_Y                          "\xc1\xb2 Y"
#define MSG_MOVE_Z                          "\xc1\xb2 Z"
#define MSG_MOVE_E                          "\xcc\xad\xba"
#define MSG_MOVE_01MM                       "\xc1\xb2 0.1mm"
#define MSG_MOVE_1MM                        "\xc1\xb2 1mm"
#define MSG_MOVE_10MM                       "\xc1\xb2 10mm"
#define MSG_SPEED                           "\xd1\xd2"
#define MSG_NOZZLE                          "\xd3\xd4"
#define MSG_BED                             "\xc4\xc7"
#define MSG_FAN_SPEED                       "\xd5\xd6\xd1\xd2"
#define MSG_FLOW                            "\xcc\xad\xd1\xd2"
#define MSG_CONTROL                         "\xd8\xd9"
#define MSG_MIN                             LCD_STR_THERMOMETER " \xda\xdb"
#define MSG_MAX                             LCD_STR_THERMOMETER " \xda\xdc"
#define MSG_FACTOR                          LCD_STR_THERMOMETER " \xdd\xde"
#define MSG_AUTOTEMP                        "\xb1\xb2\xd8\xc9"
#define MSG_ON                              "\xb3  "  // intentional space to shift wide symbol to the left
#define MSG_OFF                             "\xb5  "  // intentional space to shift wide symbol to the left
#define MSG_PID_P                           "PID-P"
#define MSG_PID_I                           "PID-I"
#define MSG_PID_D                           "PID-D"
#define MSG_PID_C                           "PID-C"
#define MSG_ACC                             "加速度"
#define MSG_JERK                            "抖动速率"
#if IS_KINEMATIC
  #define MSG_VA_JERK                       "A轴抖动速率"
  #define MSG_VB_JERK                       "B轴抖动速率"
  #define MSG_VC_JERK                       "C轴抖动速率"
#else
  #define MSG_VA_JERK                       "X轴抖动速率"
  #define MSG_VB_JERK                       "Y轴抖动速率"
  #define MSG_VC_JERK                       "Z轴抖动速率"
#endif
#define MSG_VE_JERK                         "挤出机抖动速率"
#define MSG_VMAX                            "最大进料速率"
#define MSG_VMIN                            "最小进料速率"
#define MSG_VTRAV_MIN                       "最小移动速率"
#define MSG_ACCELERATION                    _UxGT("加速度")
#define MSG_AMAX                            "最大打印加速度"
#define MSG_A_RETRACT                       "收进加速度"
#define MSG_A_TRAVEL                        "非打印移动加速度"
#define MSG_STEPS_PER_MM                    "轴步数/mm"
#if IS_KINEMATIC
  #define MSG_ASTEPS                        _UxGT("A轴步数/mm")  //"Asteps/mm"
  #define MSG_BSTEPS                        _UxGT("B轴步数/mm")  //"Bsteps/mm"
  #define MSG_CSTEPS                        _UxGT("C轴步数/mm")  //"Csteps/mm"
#else
  #define MSG_ASTEPS                        _UxGT("X轴步数/mm")  //"Xsteps/mm"
  #define MSG_BSTEPS                        _UxGT("Y轴步数/mm")  //"Ysteps/mm"
  #define MSG_CSTEPS                        _UxGT("Z轴步数/mm")  //"Zsteps/mm"
#endif
#define MSG_ESTEPS                          "挤出机步数/mm"
#define MSG_E1STEPS                         "挤出机1步数/mm"
#define MSG_E2STEPS                         "挤出机2步数/mm"
#define MSG_E3STEPS                         "挤出机3步数/mm"
#define MSG_E4STEPS                         "挤出机4步数/mm"
#define MSG_E5STEPS                         "挤出机5步数/mm"
#define MSG_TEMPERATURE                     "\xc9\xd2"
#define MSG_MOTION                          "\xdf\xb2"
#define MSG_FILAMENT                        "\xe0\xe1"
#define MSG_VOLUMETRIC_ENABLED              "测容积mm³"
#define MSG_FILAMENT_DIAM                   "耗材直径"
#define MSG_CONTRAST                        "LCD Contrast"
#define MSG_STORE_EEPROM                    "\xe5\xe6\xbe\xbf"
#define MSG_LOAD_EEPROM                     "\xe4\xab\xbe\xbf"
#define MSG_RESTORE_FAILSAFE                "恢复安全值"
#define MSG_REFRESH                         "刷新"
#define MSG_WATCH                           "\xec\xed\xee\xef"
#define MSG_PREPARE                         "\xa4\xa5"
#define MSG_TUNE                            "\xcf\xf0"
#define MSG_PAUSE_PRINT                     "\xf1\xf2\xca\xf3"
#define MSG_RESUME_PRINT                    "\xf4\xf5\xca\xf3"
#define MSG_STOP_PRINT                      "\xf2\xf6\xca\xf3"
#define MSG_CARD_MENU                       "SD\xaf\xb0"
#define MSG_NO_CARD                         "\xf9\xa8"
#define MSG_DWELL                           "休眠中..."
#define MSG_USERWAIT                        "点击继续..."
#define MSG_PRINT_ABORTED                   "\xca\xf3\x9b\xf6"
#define MSG_NO_MOVE                         "无移动"
#define MSG_KILLED                          "已杀掉"
#define MSG_STOPPED                         "已停止"
#define MSG_CONTROL_RETRACT                 "回抽长度mm"
#define MSG_CONTROL_RETRACT_SWAP            "换手回抽长度mm"
#define MSG_CONTROL_RETRACTF                "回抽速率mm/s"
#define MSG_CONTROL_RETRACT_ZLIFT           "回抽时Z轴抬升"
#define MSG_CONTROL_RETRACT_RECOVER         "回抽填装长度mm"
#define MSG_CONTROL_RETRACT_RECOVER_SWAP    "换手回抽填装长度mm"
#define MSG_CONTROL_RETRACT_RECOVERF        "回抽填装速度mm/s"
#define MSG_AUTORETRACT                     "AutoRetr."
#define MSG_FILAMENTCHANGE                  "\xea\x9c\xe0\xe1"
#define MSG_INIT_SDCARD                     "初始化SD卡"
#define MSG_CNG_SDCARD                      "更换SD卡"
#define MSG_ZPROBE_OUT                      "Z探针在热床之外"
#define MSG_HOME                            "\xbb\xbc\xbd"  // Used as MSG_HOME " " MSG_X MSG_Y MSG_Z " " MSG_FIRST
#define MSG_FIRST                           "\xa0"
#define MSG_ZPROBE_ZOFFSET                  "Z\xc0\xc1"
#define MSG_BABYSTEP_X                      "\xdb\xcf X"
#define MSG_BABYSTEP_Y                      "\xdb\xcf Y"
#define MSG_BABYSTEP_Z                      "\xdb\xcf Z"
#define MSG_ENDSTOP_ABORT                   "Endstop\x9b\xf6"
#define MSG_HEATING_FAILED_LCD              "\xc3\xc4\x9f\x9e"
#define MSG_ERR_REDUNDANT_TEMP              "Err: REDUNDANT TEMP"
#define MSG_THERMAL_RUNAWAY                 "温控失控"
#define MSG_ERR_MAXTEMP                     "Err: 最高温度"
#define MSG_ERR_MINTEMP                     "Err: 最低温度"
#define MSG_ERR_MAXTEMP_BED                 "Err: 最高热床温度"
#define MSG_ERR_MINTEMP_BED                 "Err：最低热床温度"
#define MSG_DELTA_CALIBRATE                 _UxGT("校准")
#define MSG_DELTA_CALIBRATE_X               _UxGT("校准X")
#define MSG_DELTA_CALIBRATE_Y               _UxGT("校准Y")
#define MSG_DELTA_CALIBRATE_Z               _UxGT("校准Z")
#define MSG_DELTA_CALIBRATE_CENTER          _UxGT("校准中心")

//新增翻译
#define MSG_HEATING                         "Heating..."
//#define MSG_INVERT_DIR							"\xb9\xba\x97\x98"
#define MSG_INVERT_DIR						_UxGT("方向")
#define MSG_INIT_EEPROM                     "方初始化\xbe\xbf" // "Initialize EEPROM"
#endif // LANGUAGE_CN_H
