//#include "gtest/gtest.h"
//
//int main(int argc, char** argv)
//{
//	::testing::InitGoogleTest(&argc,argv);
//	return RUN_ALL_TESTS();
//}

//#include "InputContext.h"
//#include <iostream>
//
//int main()
//{
//	InputContext context;
//	if(!context.init("inputTest.xml"))
//	{
//		std::cout<<"Erro na inicialização"<<std::endl;
//		return 1;
//	}
//
//	return 0;
//}


#include <iostream>
#include <string>
#include <functional>

#include "EngineImpl.h"

int main()
{
	IEngine* engine = new EngineImpl();

	if(!engine->init())
	{
		std::cout<<"Erro na inicialização da engine"<<std::endl;
		return 1;
	}

	engine->mainLoop();

	return 0;
}
