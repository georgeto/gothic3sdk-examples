#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Logging.h>
#include <g3sdk/util/Memory.h>

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

GEBool GE_STDCALL DoLogicalDamage_PreventInteractionNullptrDeref(Entity &Damager)
{
    // The problem is that the code tries to access the gCInteraction_PS of the
    // entity G3_Nordmar_Dungeon_SP01_Melter_Lava_Lake_01_01. But that entity
    // does not have the class, therfore the pointer is nullptr, and so crash...
    return Damager.Interaction.IsValid();
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    // Ensure that that Script_Game.dll is loaded.
    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    // This is a fix for a crash caused by the Update Pack when the Hero gets
    // close to the Hammerclan mine (due to the Lava present there).
    static mCCallHook Hook_DoLogicalDamage_PreventInteractionNullptrDeref;
    Hook_DoLogicalDamage_PreventInteractionNullptrDeref
        .Prepare(RVA_ScriptGame(0xb4619), &DoLogicalDamage_PreventInteractionNullptrDeref)
        .AddStackArg(0x160, mERegisterType_Esi) // Damager
        .SaveReg(mERegisterType_Ecx)
        .SaveReg(mERegisterType_Eax)
        .OnFalseReturnTo(RVA_ScriptGame(0xB4658))
        .InsertCall()
        .Hook();

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
