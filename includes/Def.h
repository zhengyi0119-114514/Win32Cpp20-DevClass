#pragma  once
#ifndef w32cl_api
#define w32cl_api __declspec(dllimport)
#endif
#define ref_this (*this)
#define return_ref_this return (ref_this)
