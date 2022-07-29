//#include "3ds.h"
//#include "csvc.h"
//#include "CTRPluginFramework.hpp"
#include <vector>
#include <ctime>

namespace CTRPluginFramework
{
	//about
	static const std::string About = "CTRPF v0.5.1";

    void PatchProcess(FwkSettings &settings)//ゲーム内で動くCallback
    {
    }
	
    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void OnProcessExit(void)
    {
    }

    //menu
    void InitMenu(PluginMenu &menu)
    {
	}

    std::string SystemInfomation()
    {
        char date[6400];
        std::time_t unix_time = std::time(nullptr);
        struct tm *time_struct = gmtime((const time_t *)&unix_time);
        std::string am_or_pm;
        const std::vector<std::string> kListTimeOfTheWeek{"日", "月", "火", "水", "木", "金", "土"};
        int time_of_the_week = time_struct->tm_wday; int year = time_struct->tm_year + 1900; int month = time_struct->tm_mon + 1; int day = time_struct->tm_mday; int hour_24 = time_struct->tm_hour; int hour_12; int minute = time_struct->tm_min; int second = time_struct->tm_sec;
        if (hour_24 / 12) { am_or_pm = "午後"; } else { am_or_pm = "午前"; } if (hour_24 % 12) { hour_12 = hour_24 % 12; } else { hour_12 = 12; } std::string systeminfo = Utils::Format("%d/%02d/%02d(%s) %s:%02d:%02d:%02d", year, month, day, kListTimeOfTheWeek[time_of_the_week].c_str(), am_or_pm.c_str(), hour_12, minute, second);
        return systeminfo;
    }

    void DrawCallBack(Time time)
    {
        const Screen& scr = OSD::GetTopScreen();
        scr.DrawRect(30, 4, 340, 18, Color::Black, true);
        scr.DrawRect(32, 6, 336, 14, Color::White, false);
        scr.DrawSysfont(SystemInfomation(), 35, 5, Color::White);
    }

    int main(void)
    {
        PluginMenu* menu = new PluginMenu("Menu-Clock-Frame", 1,0,0,About);
        // Synnchronize the menu with frame event

        //Add new Frame
        menu->OnNewFrame = DrawCallBack;

        menu->SynchronizeWithFrame(true);

        // Init our menu entries & folders
        InitMenu(*menu);

        // Launch menu and mainloop
        menu->Run();

        delete menu;

        // Exit plugin
		return (0);
    }
}
