#include "DodLog.h"

#include <stdio.h>
#include <stdarg.h>

namespace Dod
{
namespace
{
	const char*	spLogFileName = "dod.log";	
}

void DodLog::Printf(const char *szFormat, ...)
{
	FILE *fw = NULL;
	va_list ap;
	
	if(!spLogFileName) return;

	fw = fopen(spLogFileName, "a");
	if(!fw) return;

	va_start(ap, szFormat);
	vfprintf(fw, szFormat, ap);
	va_end(ap);

	fprintf(fw, "\r\n");

	fclose(fw);
}
}
