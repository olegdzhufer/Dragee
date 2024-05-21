#ifndef MENU_H
#define MENU_H

#include <Menulib.h>




void setup_Menu(Menu* menu ){
    Screen* setting = menu->addScreen_ptr(menu, "Setting");
    Screen* FanScreen = menu->addScreen_ptr(menu, "FAN");
    Screen* TenScreen = menu->addScreen_ptr(menu, "TEN");
    Screen* CoolScreen = menu->addScreen_ptr(menu, "COOL");

    Line* fanSet = setting->newLine_ptr(setting, "FAN", " Fan :", NULL);
    Line* coolSet = setting->newLine_ptr(setting, "COOL", " Cool :", NULL);
    Line* tenSet = setting->newLine_ptr(setting, "TEN", " Ten :", NULL);

    Line* fanStat = FanScreen->newLine_ptr(FanScreen, "STATUS", "Power :", NULL);
    Line* fanSped = FanScreen->newLine_ptr(FanScreen, "SPEED", "Speed :", NULL);

    Line* tenStat = TenScreen->newLine_ptr(TenScreen, "STATUS", "Power :", NULL);
    Line* tenTemp = TenScreen->newLine_ptr(TenScreen, "TEMP", "Temp :", NULL);
    Line* tenSetTemp = TenScreen->newLine_ptr(TenScreen, "TEMPSET", "Set tem:", NULL);

    Line* coolStat = CoolScreen->newLine_ptr(CoolScreen, "STATUS", "Power :", NULL);
    Line* cooltemp = CoolScreen->newLine_ptr(CoolScreen, "STATUS", "Temp :", NULL);


    valLine* fanSetV = fanSet->val;
    valLine* fanStataV = fanStat->val;
    valLine* fanSpeedV = fanSped->val;

    valLine* coolSetV = coolSet->val;
    valLine* coolStatV = coolStat->val;
    valLine* cooltempV = cooltemp->val;

    valLine* tenSetV = tenSet->val;
    valLine* tenStatV = tenStat->val;
    valLine* tenTempV = tenTemp->val;
    valLine* tenSetTempV = tenSetTemp->val;

    fanSetV->setBool(fanSetV, false);
    fanStataV->setBool(fanStataV, false);
    fanSpeedV->setInt(fanSpeedV, 1);

    coolSetV->setBool(coolSetV, false);
    coolStatV->setBool(coolStatV, false);
    cooltempV->setfloat(cooltempV, 0.00);

    tenSetV->setBool(tenSetV,false);
    tenStatV->setBool(tenStatV, false);
    tenTempV->setfloat(tenTempV, 0.00);
    tenSetTempV->setfloat(tenSetTempV, 0.00);

    menu->curr = setting;


    
}


#endif