#ifdef _WIN64
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/FrameworkFactory.h>
#include <cppmicroservices/BundleContext.h>
#ifdef _WIN64
#pragma warning( pop )
#endif

int main(int argc, char* argv[])
{
    US_UNUSED(argc);
    US_UNUSED(argv);
    try
    {
        auto factory = cppmicroservices::FrameworkFactory();
        auto framework = factory.NewFramework();
        framework.Init();

        auto context = framework.GetBundleContext();
        //BundleInstaller::InstallAllBundles(context);

        framework.Start();
        for (auto bundle : context.GetBundles())
        {
            bundle.Start();
        }

        auto ctx = framework.GetBundleContext();
    }
    catch (...)
    {

    }
}

