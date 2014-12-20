#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptRenderTarget.h"

namespace BansheeEngine
{
	class BS_SCR_BE_EXPORT ScriptRenderTexture : public ScriptObject <ScriptRenderTexture, ScriptRenderTargetBase>
	{
	public:
		SCRIPT_OBJ(BansheeEngineAssemblyName, "BansheeEngine", "RenderTexture")

	private:
		ScriptRenderTexture(MonoObject* instance);
	};
}