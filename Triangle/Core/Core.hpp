#pragma once

#ifndef _TRI_CORE_HEADER_HH_
#define _TRI_CORE_HEADER_HH_

#include "CommonTool.hpp"
#include "Convert.h"
#include "Timer.h"
#include "FileIO.h"
#include "HashCode.h"
#include "StrUtils.h"
#include "SysInterfaces.h"
#include "SystemEnv.h"
#include "Validators.h"
#include "TypeDefinition.h"

#ifndef WIN_NOT_IMPORT
#ifdef _WIN32
#pragma comment(lib, "Core")
#endif
#endif

#endif
