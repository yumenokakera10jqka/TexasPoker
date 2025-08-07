#pragma once

#define SAFE_DELETE( a ) {if(a){delete(a);(a)=0;}}
#define SAFE_DELETE_ARRAY( a ) {delete[](a);(a)=0;}
