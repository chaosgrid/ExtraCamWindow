

#include "IExtraCamWindowPlugin.h"




class FExtraCamWindowPlugin : public IExtraCamWindowPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FExtraCamWindowPlugin, ExtraCamWindow)



void FExtraCamWindowPlugin::StartupModule()
{
	
}


void FExtraCamWindowPlugin::ShutdownModule()
{
	
}



