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
 * Simplified Chinese
 *
 * LCD Menu Messages
 * See also http://marlinfw.org/docs/development/lcd_language.html
 *
 */
#ifndef LANGUAGE_ZH_CN_H
#define LANGUAGE_ZH_CN_H

#define CHARSIZE 3
//汉字utf-8显示支持
#define DISPLAY_CHARSET_ISO10646_CN
#define MAPPER_HASHCN


#define WELCOME_MSG                         MACHINE_NAME _UxGT("已就绪.")  //" ready."
#define MSG_BACK                            _UxGT("Back")         // ”Back“
#define MSG_SD_INSERTED                     _UxGT("SD卡已插入")  //"Card inserted"
#define MSG_SD_REMOVED                      _UxGT("SD卡已移出")  //"Card removed"
#define MSG_LCD_ENDSTOPS                    _UxGT("限位开关")  //"Endstops" // Max length 8 characters
#define MSG_MAIN                            _UxGT("主菜单")  //"Main"
#define MSG_AUTOSTART                       _UxGT("自动开始")  //"Autostart"
#define MSG_DISABLE_STEPPERS                _UxGT("关闭步进电机")  //"Disable steppers"
#define MSG_DEBUG_MENU                      _UxGT("调试菜单")    // "Debug Menu"
#define MSG_PROGRESS_BAR_TEST               _UxGT("进度条测试")  // "Progress Bar Test"
#define MSG_AUTO_HOME                       _UxGT("回原点")  //"Auto home"
#define MSG_AUTO_HOME_X                     _UxGT("回X原点")  //"Home X"
#define MSG_AUTO_HOME_Y                     _UxGT("回Y原点")  //"Home Y"
#define MSG_AUTO_HOME_Z                     _UxGT("回Z原点")  //"Home Z"
#define MSG_TMC_Z_CALIBRATION               _UxGT("⊿校准Z")  //"Calibrate Z"
#define MSG_LEVEL_BED_HOMING                _UxGT("⊿调平XYZ归原位")  //"Homing XYZ"
#define MSG_LEVEL_BED_WAITING               _UxGT("单击开始热床调平")  //"Click to Begin"
#define MSG_LEVEL_BED_NEXT_POINT            _UxGT("下个热床调平点")  //"Next Point"
#define MSG_LEVEL_BED_DONE                  _UxGT("完成热床调平")  //"Leveling Done!"
#define MSG_Z_FADE_HEIGHT                   _UxGT("dan出高度")     // "Fade Height"
#define MSG_SET_HOME_OFFSETS                _UxGT("设置原点偏移")  //"Set home offsets"
#define MSG_HOME_OFFSETS_APPLIED            _UxGT("偏移已启动")  //"Offsets applied"
#define MSG_SET_ORIGIN                      _UxGT("设置原点")  //"Set origin"
#define MSG_PREHEAT_1                       _UxGT("预热PLA")  //"Preheat PLA"
#define MSG_PREHEAT_1_N                     MSG_PREHEAT_1 _UxGT(" ")  //MSG_PREHEAT_1 " "
#define MSG_PREHEAT_1_ALL                   MSG_PREHEAT_1 _UxGT(" 所有")  //MSG_PREHEAT_1 " All"
#define MSG_PREHEAT_1_END                   MSG_PREHEAT_1 _UxGT(" 喷嘴")  //MSG_PREHEAT_1 " End"
#define MSG_PREHEAT_1_BEDONLY               MSG_PREHEAT_1 _UxGT(" 热床")  //MSG_PREHEAT_1 " Bed"
#define MSG_PREHEAT_1_SETTINGS              MSG_PREHEAT_1 _UxGT(" 设置")  //MSG_PREHEAT_1 " conf"
#define MSG_PREHEAT_2                       _UxGT("预热ABS")  //"Preheat ABS"
#define MSG_PREHEAT_2_N                     MSG_PREHEAT_2 _UxGT(" ")  //MSG_PREHEAT_2 " "
#define MSG_PREHEAT_2_ALL                   MSG_PREHEAT_2 _UxGT(" 所有")  //MSG_PREHEAT_2 " All"
#define MSG_PREHEAT_2_END                   MSG_PREHEAT_2 _UxGT(" 喷嘴")  //MSG_PREHEAT_2 " End"
#define MSG_PREHEAT_2_BEDONLY               MSG_PREHEAT_2 _UxGT(" 热床")  //MSG_PREHEAT_2 " Bed"
#define MSG_PREHEAT_2_SETTINGS              MSG_PREHEAT_2 _UxGT(" 设置")  //MSG_PREHEAT_2 " conf"
#define MSG_COOLDOWN                        _UxGT("温度-")  //"Cooldown"
#define MSG_SWITCH_PS_ON                    _UxGT("电源打开")  //"Switch power on"
#define MSG_SWITCH_PS_OFF                   _UxGT("电源关闭")  //"Switch power off"
#define MSG_EXTRUDE                         _UxGT("挤出")  //"Extrude"
#define MSG_RETRACT                         _UxGT("回抽")  //"Retract"
#define MSG_MOVE_AXIS                       _UxGT("移动轴")  //"Move axis"
#define MSG_BED_LEVELING                    _UxGT("调平热床")  //"Bed leveling"
#define MSG_LEVEL_BED                       _UxGT("调平热床")  //"Level bed"
#define MSG_LEVEL_CORNERS                   _UxGT("调平边⊿") // "Level corners"

#define MSG_NEXT_CORNER                     _UxGT("下个边⊿") // "Next corner"
#define MSG_EDITING_STOPPED                 _UxGT("网格编辑已停止") // "Mesh Editing Stopped"

#define MSG_USER_MENU                       _UxGT("定制Commands") // "Custom Commands"
#define MSG_UBL_DOING_G29                   _UxGT("Doing G29") // "Doing G29"
#define MSG_UBL_UNHOMED                     _UxGT("先回XYZ原点") // "Home XYZ first"
#define MSG_UBL_TOOLS                       _UxGT("UBL Tools") // "UBL Tools"
#define MSG_UBL_LEVEL_BED                   _UxGT("统一热床调平(UBL)") // "Unified Bed Leveling"
#define MSG_UBL_MANUAL_MESH                 _UxGT("自定制作网格") // "Manually Build Mesh"

#define MSG_UBL_BC_INSERT                   _UxGT("play⊿&测量") // "Place shim & measure"
#define MSG_UBL_BC_INSERT2                  _UxGT("测量") // "Measure"
#define MSG_UBL_BC_REMOVE                   _UxGT("移出&测量热床") // "Remove & measure bed"
#define MSG_UBL_MOVING_TO_NEXT              _UxGT("移动到下一个") // "Moving to next"
#define MSG_UBL_ACTIVATE_MESH               _UxGT("打开UBL") // "Activate UBL"
#define MSG_UBL_DEACTIVATE_MESH             _UxGT("关闭UBL") // "Deactivate UBL"
#define MSG_UBL_SET_BED_TEMP                _UxGT("设置热床温度") // "Bed Temp"
#define MSG_UBL_SET_HOTEND_TEMP             _UxGT("热边温度") // "Hotend Temp"
#define MSG_UBL_MESH_EDIT                   _UxGT("网格编辑") // "Mesh Edit"
#define MSG_UBL_EDIT_CUSTOM_MESH            _UxGT("编辑自定网格") // "Edit Custom Mesh"
#define MSG_UBL_FINE_TUNE_MESH              _UxGT("调整网格") // "Fine Tuning Mesh"
#define MSG_UBL_DONE_EDITING_MESH           _UxGT("完成编辑网格") // "Done Editing Mesh"
#define MSG_UBL_BUILD_CUSTOM_MESH           _UxGT("制作自定网格") // "Build Custom Mesh"
#define MSG_UBL_BUILD_MESH_MENU             _UxGT("制作网格") // "Build Mesh"
#define MSG_UBL_BUILD_PLA_MESH              _UxGT("制作PLA网格") // "Build PLA Mesh"
#define MSG_UBL_BUILD_ABS_MESH              _UxGT("制作ABS网格") // "Build ABS Mesh"
#define MSG_UBL_BUILD_COLD_MESH             _UxGT("制作冷网格") // "Build Cold Mesh"
#define MSG_UBL_MESH_HEIGHT_ADJUST          _UxGT("调整网格高度") // "Adjust Mesh Height"
#define MSG_UBL_MESH_HEIGHT_AMOUNT          _UxGT("高度量") // "Height Amount"
#define MSG_UBL_VALIDATE_MESH_MENU          _UxGT("设定网格") // "Validate Mesh"
#define MSG_UBL_VALIDATE_PLA_MESH           _UxGT("设定PLA网格") // "Validate PLA Mesh"
#define MSG_UBL_VALIDATE_ABS_MESH           _UxGT("设定ABS网格") // "Validate ABS Mesh"
#define MSG_UBL_VALIDATE_CUSTOM_MESH        _UxGT("设定自定网格") // "Validate Custom Mesh"
#define MSG_UBL_CONTINUE_MESH               _UxGT("继续热床网格") // "Continue Bed Mesh"
#define MSG_UBL_MESH_LEVELING               _UxGT("网格调平") // "Mesh Leveling"
#define MSG_UBL_3POINT_MESH_LEVELING        _UxGT("三点调平") // "3-Point Leveling"
#define MSG_UBL_GRID_MESH_LEVELING          _UxGT("网格调平") // "Grid Mesh Leveling"
#define MSG_UBL_MESH_LEVEL                  _UxGT("调平网格") // "Level Mesh"
#define MSG_UBL_SIDE_POINTS                 _UxGT("边点") // "Side Points"
#define MSG_UBL_MAP_TYPE                    _UxGT("Map Type") // "Map Type"
#define MSG_UBL_OUTPUT_MAP                  _UxGT("输出网格Map") // "Output Mesh Map"
#define MSG_UBL_OUTPUT_MAP_HOST             _UxGT("输出到主机") // "Output for Host"
#define MSG_UBL_OUTPUT_MAP_CSV              _UxGT("输出到CSV") // "Output for CSV"
#define MSG_UBL_OUTPUT_MAP_BACKUP           _UxGT("输出到Backup") // "Off Printer Backup"
#define MSG_UBL_INFO_UBL                    _UxGT("输出UBL信息") // "Output UBL Info"
#define MSG_UBL_EDIT_MESH_MENU              _UxGT("编辑网格") // "Edit Mesh"
#define MSG_UBL_FILLIN_AMOUNT               _UxGT("填充量") // "Fill-in Amount"
#define MSG_UBL_MANUAL_FILLIN               _UxGT("自定填充") // "Manual Fill-in"
#define MSG_UBL_SMART_FILLIN                _UxGT("AI填充") // "Smart Fill-in"
#define MSG_UBL_FILLIN_MESH                 _UxGT("填充网格") // "Fill-in Mesh"
#define MSG_UBL_INVALIDATE_ALL              _UxGT("作废所有") // "Invalidate All"
#define MSG_UBL_INVALIDATE_CLOSEST          _UxGT("作废Closest") // "Invalidate Closest"
#define MSG_UBL_FINE_TUNE_ALL               _UxGT("调整所有") // "Fine Tune All"
#define MSG_UBL_FINE_TUNE_CLOSEST           _UxGT("调整Closest") // "Fine Tune Closest"
#define MSG_UBL_STORAGE_MESH_MENU           _UxGT("网格存储") // "Mesh Storage"
#define MSG_UBL_STORAGE_SLOT                _UxGT("存储位") // "Memory Slot"
#define MSG_UBL_LOAD_MESH                   _UxGT("加载热床网格") // "Load Bed Mesh"
#define MSG_UBL_SAVE_MESH                   _UxGT("保存热床网格") // "Save Bed Mesh"
#define MSG_MESH_LOADED                     _UxGT("网格 %i 已加载") // "Mesh %i loaded"
#define MSG_MESH_SAVED                      _UxGT("网格 %i 已保存") // "Mesh %i saved"
#define MSG_NO_STORAGE                      _UxGT("无存储") // "No storage"
#define MSG_UBL_SAVE_ERROR                  _UxGT("Err: UBL保存") // "Err: UBL Save"
#define MSG_UBL_RESTORE_ERROR               _UxGT("Err: UBL Restore") // "Err: UBL Restore"
#define MSG_UBL_Z_OFFSET_STOPPED            _UxGT("Z偏移已停止") // "Z-Offset Stopped"
#define MSG_UBL_STEP_BY_STEP_MENU           _UxGT("一步步UBL") // "Step-By-Step UBL"

#define MSG_LED_CONTROL                     _UxGT("LED控制") // "LED Control")
#define MSG_LEDS                            _UxGT("LED") // "Lights")
#define MSG_LED_PRESETS                     _UxGT("LED预置") // "Light Presets")
#define MSG_SET_LEDS_RED                    _UxGT("Red") // "Red")
#define MSG_SET_LEDS_ORANGE                 _UxGT("Orange") // "Orange")
#define MSG_SET_LEDS_YELLOW                 _UxGT("Yellow") // "Yellow")
#define MSG_SET_LEDS_GREEN                  _UxGT("Green") // "Green")
#define MSG_SET_LEDS_BLUE                   _UxGT("Blue") // "Blue")
#define MSG_SET_LEDS_INDIGO                 _UxGT("Indigo") // "Indigo")
#define MSG_SET_LEDS_VIOLET                 _UxGT("Violet") // "Violet")
#define MSG_SET_LEDS_WHITE                  _UxGT("White") // "White")
#define MSG_SET_LEDS_DEFAULT                _UxGT("Default") // "Default")
#define MSG_CUSTOM_LEDS                     _UxGT("定制LED") // "Custom Lights")
#define MSG_INTENSITY_R                     _UxGT("Red Intensity") // "Red Intensity")
#define MSG_INTENSITY_G                     _UxGT("Green Intensity") // "Green Intensity")
#define MSG_INTENSITY_B                     _UxGT("Blue Intensity") // "Blue Intensity")
#define MSG_INTENSITY_W                     _UxGT("White Intensity") // "White Intensity")
#define MSG_LED_BRIGHTNESS                  _UxGT("Brightness") // "Brightness")
#define MSG_MOVING                          _UxGT("移动 ...") // "Moving...")
#define MSG_FREE_XY                         _UxGT("停止 XY") // "Free XY")

#define MSG_MOVE_X                          _UxGT("移动X")  //"Move X"
#define MSG_MOVE_Y                          _UxGT("移动Y")  //"Move Y"
#define MSG_MOVE_Z                          _UxGT("移动Z")  //"Move Z"
#define MSG_MOVE_E                          _UxGT("挤出机")  //"Extruder"
#define MSG_MOVE_01MM                       _UxGT("移动 0.1 mm")  //"Move 0.1mm"
#define MSG_MOVE_1MM                        _UxGT("移动 1 mm")  //"Move 1mm"
#define MSG_MOVE_10MM                       _UxGT("移动 10 mm")  //"Move 10mm"
#define MSG_SPEED                           _UxGT("速度")  //"Speed"
#define MSG_BED_Z                           _UxGT("热床Z")  //"Bed Z"
#define MSG_NOZZLE                          _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" 喷嘴")  //"Nozzle" 噴嘴
#define MSG_BED                             _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" 热床")  //"Bed"
#define MSG_FAN_SPEED                       _UxGT("风扇速度")  //"Fan speed"
#define MSG_EXTRA_FAN_SPEED                 _UxGT("Extra风扇速度") // "Extra fan speed"
#define MSG_FLOW                            _UxGT("挤出速度")  //"Flow"
#define MSG_CONTROL                         _UxGT("控制")  //"Control"
#define MSG_MIN                             _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" 最小") //" " LCD_STR_THERMOMETER " Min"
#define MSG_MAX                             _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" 最大")  //" " LCD_STR_THERMOMETER " Max"
#define MSG_FACTOR                          _UxGT(" ") LCD_STR_THERMOMETER _UxGT(" Fact")  //" " LCD_STR_THERMOMETER " Fact"
#define MSG_AUTOTEMP                        _UxGT("自动控温")  //"Autotemp"
#define MSG_ON                              _UxGT("开 ")  //"On "
#define MSG_OFF                             _UxGT("关 ")  //"Off"
#define MSG_PID_P                           _UxGT("PID-P")  //"PID-P"
#define MSG_PID_I                           _UxGT("PID-I")  //"PID-I"
#define MSG_PID_D                           _UxGT("PID-D")  //"PID-D"
#define MSG_PID_C                           _UxGT("PID-C")  //"PID-C"
#define MSG_SELECT                          _UxGT("Select")  //"Select"
#define MSG_ACC                             _UxGT("加速度")  //"Accel" acceleration
#define MSG_JERK                            _UxGT("抖动速度")  // "Jerk"
#if IS_KINEMATIC
  #define MSG_VA_JERK                       _UxGT("A轴抖动速度")  //"Va-jerk"
  #define MSG_VB_JERK                       _UxGT("B轴抖动速度")  //"Vb-jerk"
  #define MSG_VC_JERK                       _UxGT("C轴抖动速度")  //"Vc-jerk"
#else
  #define MSG_VA_JERK                       _UxGT("X轴抖动速度")  //"Vx-jerk"
  #define MSG_VB_JERK                       _UxGT("Y轴抖动速度")  //"Vy-jerk"
  #define MSG_VC_JERK                       _UxGT("Z轴抖动速度")  //"Vz-jerk"
#endif
#define MSG_VE_JERK                         _UxGT("挤出机抖动速度")  //"Ve-jerk"
#define MSG_VELOCITY                        _UxGT("速度")          // "Velocity"
#define MSG_VMAX                            _UxGT("最大进料速度")  //"Vmax " max_feedrate_mm_s
#define MSG_VMIN                            _UxGT("最小进料速度")  //"Vmin"  min_feedrate_mm_s
#define MSG_VTRAV_MIN                       _UxGT("最小移动速度")  //"VTrav min" min_travel_feedrate_mm_s, (target) speed of the move
#define MSG_ACCELERATION                    _UxGT("加速度")       // "Acceleration"
#define MSG_AMAX                            _UxGT("最大打印加速度")  //"Amax " max_acceleration_mm_per_s2, acceleration in units/s^2 for print moves
#define MSG_A_RETRACT                       _UxGT("回抽加速度")  //"A-retract" retract_acceleration, E acceleration in mm/s^2 for retracts
#define MSG_A_TRAVEL                        _UxGT("轴移动加速度")  //"A-travel" travel_acceleration, X, Y, Z acceleration in mm/s^2 for travel (non printing) moves
#define MSG_STEPS_PER_MM                    _UxGT("轴步进/mm")  //"Steps/mm" axis_steps_per_mm, axis steps-per-unit G92
#if IS_KINEMATIC
  #define MSG_ASTEPS                        _UxGT("A轴步进/mm")  //"Asteps/mm"
  #define MSG_BSTEPS                        _UxGT("B轴步进/mm")  //"Bsteps/mm"
  #define MSG_CSTEPS                        _UxGT("C轴步进/mm")  //"Csteps/mm"
#else
  #define MSG_ASTEPS                        _UxGT("X轴步进/mm")  //"Xsteps/mm"
  #define MSG_BSTEPS                        _UxGT("Y轴步进/mm")  //"Ysteps/mm"
  #define MSG_CSTEPS                        _UxGT("Z轴步进/mm")  //"Zsteps/mm"
#endif
#define MSG_ESTEPS                          _UxGT("挤出机步进/mm")  //"Esteps/mm"
#define MSG_E1STEPS                         _UxGT("挤出机1步进/mm") //"E1steps/mm"
#define MSG_E2STEPS                         _UxGT("挤出机2步进/mm") //"E2steps/mm"
#define MSG_E3STEPS                         _UxGT("挤出机3步进/mm") //"E3steps/mm"
#define MSG_E4STEPS                         _UxGT("挤出机4步进/mm") //"E4steps/mm"
#define MSG_E5STEPS                         _UxGT("挤出机5步进/mm") //"E5steps/mm"
#define MSG_TEMPERATURE                     _UxGT("温度")  //"Temperature"
#define MSG_MOTION                          _UxGT("运动")  //"Motion"
#define MSG_FILAMENT                        _UxGT("耗材")  //"Filament" lcd_control_volumetric_menu
#define MSG_VOLUMETRIC_ENABLED              _UxGT("E in mm³")  //"E in mm3" volumetric_enabled
#define MSG_FILAMENT_DIAM                   _UxGT("Fil. Dia.")  //"Fil. Dia."
#define MSG_FILAMENT_UNLOAD                 _UxGT("Unload mm") // "Unload mm"
#define MSG_FILAMENT_LOAD                   _UxGT("Load mm")   // "Load mm"
#define MSG_ADVANCE_K                       _UxGT("Advance K") // "Advance K"
#define MSG_CONTRAST                        _UxGT("LCD contrast")  //"LCD contrast"
#define MSG_STORE_EEPROM                    _UxGT("保存设置")  //"Store memory"
#define MSG_LOAD_EEPROM                     _UxGT("载入设置")  //"Load memory"
#define MSG_RESTORE_FAILSAFE                _UxGT("恢复原始设置")  //"Restore failsafe"
#define MSG_INIT_EEPROM                     _UxGT("Init. EEPROM") // "Initialize EEPROM"
#define MSG_REFRESH                         _UxGT("Refresh")  //"Refresh"
#define MSG_WATCH                           _UxGT("信息")  //"Info screen"
#define MSG_PREPARE                         _UxGT("准备")  //"Prepare"
#define MSG_TUNE                            _UxGT("调整")  //"Tune"
#define MSG_PAUSE_PRINT                     _UxGT("暂停打印")  //"Pause print"
#define MSG_RESUME_PRINT                    _UxGT("恢复打印")  //"Resume print"
#define MSG_STOP_PRINT                      _UxGT("停止打印")  //"Stop print"
#define MSG_CARD_MENU                       _UxGT("SD卡菜单")  //"Print from SD"
#define MSG_NO_CARD                         _UxGT("无SD卡")  //"No SD card"
#define MSG_DWELL                           _UxGT("休眠...")  //"Sleep..."
#define MSG_USERWAIT                        _UxGT("点击继续...")  //"Click to resume..."
#define MSG_PRINT_PAUSED                    _UxGT("暂停打印") // "Print paused"
#define MSG_PRINT_ABORTED                   _UxGT("已中止打印")  //"Print aborted"
#define MSG_NO_MOVE                         _UxGT("无移动")  //"No move."
#define MSG_KILLED                          _UxGT("已关闭")  //"KILLED. "
#define MSG_STOPPED                         _UxGT("已停止")  //"STOPPED. "
#define MSG_CONTROL_RETRACT                 _UxGT("回抽长度mm")  //"Retract mm" retract_length, retract length (positive mm)
#define MSG_CONTROL_RETRACT_SWAP            _UxGT("换shou回抽长度mm")  //"Swap Re.mm" swap_retract_length, swap retract length (positive mm), for extruder change
#define MSG_CONTROL_RETRACTF                _UxGT("回抽速度mm/s")  //"Retract  V" retract_feedrate_mm_s, feedrate for retracting (mm/s)
#define MSG_CONTROL_RETRACT_ZLIFT           _UxGT("Hop mm")  //"Hop mm" retract_zlift, retract Z-lift
#define MSG_CONTROL_RETRACT_RECOVER         _UxGT("回抽恢复长度mm")  //"UnRet +mm" retract_recover_length, additional recover length (mm, added to retract length when recovering)
#define MSG_CONTROL_RETRACT_RECOVER_SWAP    _UxGT("换shou回抽恢复长度mm")  //"S UnRet+mm" swap_retract_recover_length, additional swap recover length (mm, added to retract length when recovering from extruder change)
#define MSG_CONTROL_RETRACT_RECOVERF        _UxGT("回抽恢复hou进料速度mm/s")  //"UnRet  V" retract_recover_feedrate_mm_s, feedrate for recovering from retraction (mm/s)
#define MSG_CONTROL_RETRACT_RECOVER_SWAPF   _UxGT("S UnRet V") // "S UnRet V"
#define MSG_AUTORETRACT                     _UxGT("自动抽回")  //"AutoRetr." autoretract_enabled,
#define MSG_FILAMENTCHANGE                  _UxGT("更换耗材")  //"Change filament"
#define MSG_FILAMENTLOAD                    _UxGT("加载耗材") // "Load filament"
#define MSG_FILAMENTUNLOAD                  _UxGT("卸载耗材") // "Unload filament"
#define MSG_FILAMENTUNLOAD_ALL              _UxGT("卸载ALL") // "Unload All"
#define MSG_INIT_SDCARD                     _UxGT("Init. SD卡")  //"Init. SD card"
#define MSG_CNG_SDCARD                      _UxGT("更换SD卡")  //"Change SD card"
#define MSG_ZPROBE_OUT                      _UxGT("Z温控偏移热床")  //"Z probe out. bed" Z probe is not within the physical limits
#define MSG_SKEW_FACTOR                     _UxGT("偏斜Factor") // "Skew Factor"
#define MSG_BLTOUCH                         _UxGT("BLTouch")     // "BLTouch"
#define MSG_BLTOUCH_SELFTEST                _UxGT("BLTouch 自测试") // "BLTouch Self-Test"
#define MSG_BLTOUCH_RESET                   _UxGT("Reset BLTouch")  // "Reset BLTouch"
#define MSG_BLTOUCH_DEPLOY                  _UxGT("设置BLTouch") // "Deploy BLTouch"
#define MSG_BLTOUCH_STOW                    _UxGT("加载BLTouch")   // "Stow BLTouch"
#define MSG_HOME                            _UxGT("归位")  //"Home"  // Used as MSG_HOME " " MSG_X MSG_Y MSG_Z " " MSG_FIRST
#define MSG_FIRST                           _UxGT("先")  //"first"
#define MSG_ZPROBE_ZOFFSET                  _UxGT("Z偏移")  //"Z Offset"
#define MSG_BABYSTEP_X                      _UxGT("小量调整X轴")  //"Babystep X" lcd_babystep_x, Babystepping enables the user to control the axis in tiny amounts
#define MSG_BABYSTEP_Y                      _UxGT("小量调整Y轴")  //"Babystep Y"
#define MSG_BABYSTEP_Z                      _UxGT("小量调整Z轴")  //"Babystep Z"
#define MSG_ENDSTOP_ABORT                   _UxGT("限位停止")  //"Endstop abort"
#define MSG_HEATING_FAILED_LCD              _UxGT("加热失败")  //"Heating failed"
#define MSG_ERR_REDUNDANT_TEMP              _UxGT("错误：REDUNDANT TEMP")  //"Err: REDUNDANT TEMP"
#define MSG_THERMAL_RUNAWAY                 _UxGT("温控失控")  //"THERMAL RUNAWAY"
#define MSG_ERR_MAXTEMP                     _UxGT("Err：最高温度")  //"Err: MAXTEMP"
#define MSG_ERR_MINTEMP                     _UxGT("Err：最低温度")  //"Err: MINTEMP"
#define MSG_ERR_MAXTEMP_BED                 _UxGT("Err：最高热床温度")  //"Err: MAXTEMP BED"
#define MSG_ERR_MINTEMP_BED                 _UxGT("Err：最低热床温度")  //"Err: MINTEMP BED"
#define MSG_ERR_Z_HOMING                    MSG_HOME _UxGT(" ") MSG_X MSG_Y _UxGT(" ") MSG_FIRST
#define MSG_HALTED                          _UxGT("打印机已停止")  //"PRINTER HALTED"
#define MSG_PLEASE_RESET                    _UxGT("Please reset")  //"Please reset"
#define MSG_SHORT_DAY                       _UxGT("d")  //"d" // One character only
#define MSG_SHORT_HOUR                      _UxGT("h")  //"h" // One character only
#define MSG_SHORT_MINUTE                    _UxGT("m")  //"m" // One character only
#define MSG_HEATING                         _UxGT("加热中.")  //"Heating..."
#define MSG_BED_HEATING                     _UxGT("加热热床中.")  //"Bed Heating..."
#define MSG_DELTA_CALIBRATE                 _UxGT("⊿校准")  //"Delta Calibration"
#define MSG_DELTA_CALIBRATE_X               _UxGT("⊿校准X")  //"Calibrate X"
#define MSG_DELTA_CALIBRATE_Y               _UxGT("⊿校准Y")  //"Calibrate Y"
#define MSG_DELTA_CALIBRATE_Z               _UxGT("⊿校准Z")  //"Calibrate Z"
#define MSG_DELTA_CALIBRATE_CENTER          _UxGT("⊿校准中心")  //"Calibrate Center"
#define MSG_DELTA_SETTINGS                  _UxGT("⊿设置") // "Delta Settings"
#define MSG_DELTA_AUTO_CALIBRATE            _UxGT("⊿自动校准") // "Auto Calibration"
#define MSG_DELTA_HEIGHT_CALIBRATE          _UxGT("设置⊿高度") // "Set Delta Height"
#define MSG_DELTA_DIAG_ROD                  _UxGT("⊿Diag Rod") // "Diag Rod"
#define MSG_DELTA_HEIGHT                    _UxGT("⊿高度") // "Height"
#define MSG_DELTA_RADIUS                    _UxGT("⊿Radius") // "Radius"
#define MSG_INFO_MENU                       _UxGT("About打印机")  //"About Printer"
#define MSG_INFO_PRINTER_MENU               _UxGT("打印机信息")  //"Printer Info"
#define MSG_3POINT_LEVELING                 _UxGT("三点调平") // "3-Point Leveling"
#define MSG_LINEAR_LEVELING                 _UxGT("Linear调平") // "Linear Leveling"
#define MSG_BILINEAR_LEVELING               _UxGT("Bilinear调平") // "Bilinear Leveling"
#define MSG_UBL_LEVELING                    _UxGT("统一热床调平(UBL)") // "Unified Bed Leveling"
#define MSG_MESH_LEVELING                   _UxGT("网格调平") // "Mesh Leveling"
#define MSG_INFO_STATS_MENU                 _UxGT("打印机统")  //"Printer Stats"
#define MSG_INFO_BOARD_MENU                 _UxGT("Board信息")  //"Board Info"
#define MSG_INFO_THERMISTOR_MENU            _UxGT("温度ji")  //"Thermistors"
#define MSG_INFO_EXTRUDERS                  _UxGT("挤出机")  //"Extruders"
#define MSG_INFO_BAUDRATE                   _UxGT("Baud")  //"Baud"
#define MSG_INFO_PROTOCOL                   _UxGT("Protocol")  //"Protocol"
#define MSG_CASE_LIGHT                      _UxGT("LED") // "Case light"
#define MSG_CASE_LIGHT_BRIGHTNESS           _UxGT("LED BRIGHTNESS") // "Light BRIGHTNESS"

#if LCD_WIDTH > 19
#define MSG_INFO_PRINT_COUNT              _UxGT("打印量")  //"Print Count"
#define MSG_INFO_COMPLETED_PRINTS         _UxGT("已完成")  //"Completed"
#define MSG_INFO_PRINT_TIME               _UxGT("ALL打印time")  //"Total print time"
#define MSG_INFO_PRINT_LONGEST            _UxGT("最长打印time")  //"Longest job time"
#define MSG_INFO_PRINT_FILAMENT           _UxGT("挤出ALL量")  //"Extruded total"
#else
#define MSG_INFO_PRINT_COUNT              _UxGT("打印量")  //"Prints"
#define MSG_INFO_COMPLETED_PRINTS         _UxGT("完成")  //"Completed"
#define MSG_INFO_PRINT_TIME               _UxGT("ALL")  //"Total"
#define MSG_INFO_PRINT_LONGEST            _UxGT("最长")  //"Longest"
#define MSG_INFO_PRINT_FILAMENT           _UxGT("已挤出")  //"Extruded"
#endif

#define MSG_INFO_MIN_TEMP                   _UxGT("最低温度")  //"Min Temp"
#define MSG_INFO_MAX_TEMP                   _UxGT("最高温度")  //"Max Temp"
#define MSG_INFO_PSU                        _UxGT("电源")  //"Power Supply"
#define MSG_DRIVE_STRENGTH                  _UxGT("Drive Strength") // "Drive Strength"
#define MSG_DAC_PERCENT                     _UxGT("Driver %") // "Driver %"
#define MSG_DAC_EEPROM_WRITE                _UxGT("保存设置") // "DAC EEPROM Write"
#define MSG_FILAMENT_CHANGE_HEADER_PAUSE    _UxGT("打印已暂停") // "PRINT PAUSED"
#define MSG_FILAMENT_CHANGE_HEADER_LOAD     _UxGT("加载耗材") // "LOAD FILAMENT"
#define MSG_FILAMENT_CHANGE_HEADER_UNLOAD   _UxGT("卸载耗材") // "UNLOAD FILAMENT"
#define MSG_FILAMENT_CHANGE_OPTION_HEADER   _UxGT("恢复OPTIONS:") // "RESUME OPTIONS:"
#define MSG_FILAMENT_CHANGE_OPTION_PURGE    _UxGT("移出more") // "Purge more"
#define MSG_FILAMENT_CHANGE_OPTION_RESUME   _UxGT("恢复打印")  //"Resume print"
#define MSG_FILAMENT_CHANGE_NOZZLE          _UxGT(" 喷嘴: ") // "  Nozzle: "
#define MSG_ERR_HOMING_FAILED               _UxGT("回原点失败") // "Homing failed"
#define MSG_ERR_PROBING_FAILED              _UxGT("温控启动失败") // "Probing failed"
#define MSG_M600_TOO_COLD                   _UxGT("M600: 温度低") // "M600: Too cold"

#if LCD_HEIGHT >= 4
#define MSG_FILAMENT_CHANGE_INIT_1          _UxGT("等待开始")  //"Wait for start"
#define MSG_FILAMENT_CHANGE_INIT_2          _UxGT("耗材")  //"of the filament"
#define MSG_FILAMENT_CHANGE_INIT_3          _UxGT("change")  //"change"
#define MSG_FILAMENT_CHANGE_UNLOAD_1        _UxGT("等待")  //"Wait for"
#define MSG_FILAMENT_CHANGE_UNLOAD_2        _UxGT("卸下耗材")  //"filament unload"
#define MSG_FILAMENT_CHANGE_INSERT_1        _UxGT("插入耗材")  //"Insert filament"
#define MSG_FILAMENT_CHANGE_INSERT_2        _UxGT("& ○")  //"and press button"
#define MSG_FILAMENT_CHANGE_INSERT_3        _UxGT("继续 ...")  //"to continue..."
#define MSG_FILAMENT_CHANGE_HEAT_1          _UxGT("按下○") // "Press button to"
#define MSG_FILAMENT_CHANGE_HEAT_2          _UxGT("加热喷嘴.") // "heat nozzle."
#define MSG_FILAMENT_CHANGE_HEATING_1       _UxGT("加热喷嘴中 ...") // "Heating nozzle"
#define MSG_FILAMENT_CHANGE_HEATING_2       _UxGT("Please等待 ...") // "Please wait..."
#define MSG_FILAMENT_CHANGE_LOAD_1          _UxGT("等待")  //"Wait for"
#define MSG_FILAMENT_CHANGE_LOAD_2          _UxGT("进料")  //"filament load"
#define MSG_FILAMENT_CHANGE_PURGE_1         _UxGT("等待") // "Wait for"
#define MSG_FILAMENT_CHANGE_PURGE_2         _UxGT("耗材移出") // "filament purge"
#define MSG_FILAMENT_CHANGE_RESUME_1        _UxGT("等待打印")  //"Wait for print"
#define MSG_FILAMENT_CHANGE_RESUME_2        _UxGT("恢复")  //"to resume"

#else // LCD_HEIGHT < 4
#define MSG_FILAMENT_CHANGE_INIT_1          _UxGT("Please等待 ...")  //"Please wait..."
#define MSG_FILAMENT_CHANGE_UNLOAD_1        _UxGT("EXIT ...")  //"Ejecting..."
#define MSG_FILAMENT_CHANGE_INSERT_1        _UxGT("插入&单击")  //"Insert and Click"
#define MSG_FILAMENT_CHANGE_HEATING_1       _UxGT("加热中 ...") // "Heating..."
#define MSG_FILAMENT_CHANGE_LOAD_1          _UxGT("加载中 ...")  //"Loading..."
#define MSG_FILAMENT_CHANGE_PURGE_1         _UxGT("移出中 ...") // "Purging..."
#define MSG_FILAMENT_CHANGE_RESUME_1        _UxGT("恢复中 ...")  //"Resuming..."
#endif // LCD_HEIGHT < 4

//新增翻译
#define MSG_X_INVERT_DIR					_UxGT("X轴电机方向")
#define MSG_Y_INVERT_DIR					_UxGT("Y轴电机方向")
#define MSG_Z_INVERT_DIR					_UxGT("Z轴电机方向")
#define MSG_E_INVERT_DIR					_UxGT("E轴电机方向")
#define MSG_INVERT_DIR						_UxGT("电机方向")
#define MSG_SETTING_MENU					_UxGT("设置菜单")
#define MSG_LCD_SOFT_ENDSTOPS     _UxGT("SOFT限位")
#define MSG_STEPS_SETTING					_UxGT("步进设置")
#define MSG_PRINTING              _UxGT("打印中 ...")
#define MSG_HOMING_DES            _UxGT("回原点XY坐标")
#define MSG_HOMING_DES_X            _UxGT("回原点X坐标")
#define MSG_HOMING_DES_Y            _UxGT("回原点Y坐标")
#define MSG_ENCODER_DIR           _UxGT("Encoder方向反转") //旋钮方向反转
#define MSG_ALLOW_COLD_EXTRUDE    _UxGT("启用冷挤出")
#endif // LANGUAGE_ZH_CN_H
