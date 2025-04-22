#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Logging.h>
#include <g3sdk/util/Memory.h>

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

GEBool bOnlyWeaponWarning = GEFalse;

void LoadSettings()
{
    eCConfigFile config = eCConfigFile();
    if (config.ReadFile(bCString("nosvm.ini")))
    {
        bOnlyWeaponWarning = config.GetBool(bCString("Game"), bCString("Game.OnlyWeaponWarning"), GEFalse);
    }
}

mCCallHook Hook_StartSayEx;
void GE_STDCALL StartSayEx(Entity &, bCString, bCString a_str2, GEBool)
{
    if (!bOnlyWeaponWarning || a_str2.Contains("WeaponDown"))
    {
        Entity *pSpeaker = Hook_StartSayEx.GetSelf<Entity *>();
        bCUnicodeString strMessage = gCSVMManager::GetLocString(pSpeaker->NPC.Voice, a_str2);
        bCUnicodeString strEntityName = eCLocString("FO_" + pSpeaker->GetName());

        if (!strMessage.IsEmpty() && !strEntityName.IsEmpty())
            gui2.PrintGameMessage(strEntityName + L": " + strMessage, gEGameMessageType_Yellow);
    }
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    // Ensure that that Script_Game.dll is loaded.
    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    LoadSettings();
    Hook_StartSayEx.Hook(RVA_Script(0x2095A), &StartSayEx, mCBaseHook::mEHookType_ThisCall);

    return &GetScriptInit();
}

//
// Entry Point
//

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH: ::DisableThreadLibraryCalls(hModule); break;
        case DLL_PROCESS_DETACH: break;
    }
    return TRUE;
}
