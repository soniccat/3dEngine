
#include <stdio.h>

#include <assert.h>
#include <vector>
#include <string>
#include <stack>
using namespace std;

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/shared_array.hpp>
using namespace boost;

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include <btBulletDynamicsCommon.h>

#include "SEAllocator.h"
#include "SEMemory.h"