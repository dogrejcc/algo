#include "tools.h"
void log(const loglevel& level,std::string msg)
{
	std::string header;
	switch (level){
		case info:
			header="[INFO]  ";
			break;
		case warn:
			header="[WARN]  ";
			break;
		case fatal:
			header="[FATAL]  "; 
			break;
		default:
			;
	}
	std::cout<<header+msg<<'\n';
}
