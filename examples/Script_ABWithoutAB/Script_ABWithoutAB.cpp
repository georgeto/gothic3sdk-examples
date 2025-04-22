#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Logging.h>
#include <g3sdk/util/Memory.h>

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    // Ensure that that Script_Game.dll is loaded.
    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    WriteNops(RVA_ScriptGame(0x609E5), 0x609FC - 0x609E5);

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
