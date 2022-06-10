#include <wchar.h>
#include <Windows.h>
#include <sddl.h>
#include <iostream>
#include <string>
#include <string>
#include <comutil.h>
#include<vector>
#include<algorithm>
//including JNI headers
#include "jni.h"
#include "com_ManagerApp_handler_GetADdata.h"
//dll headers
#include "../../../addata separate C++ files/ADUserDetail/ADUserDetail/ADUserDetail.h"
using namespace std;

vector<string> GetActiveDirectoryUsersData();

//JNIEXPORT jobject JNICALL Java_com_ManagerApp_handler_GetADdata_GetData(JNIEnv*, jobject, jstring);
JNIEXPORT jobject JNICALL Java_com_ManagerApp_handler_GetADdata_GetData(JNIEnv* env, jobject GetADdata, jstring jpath)
{
	jclass java_util_ArrayList;
	jmethodID java_util_ArrayList_;
	jmethodID java_util_ArrayList_size;
	jmethodID java_util_ArrayList_get;
	jmethodID java_util_ArrayList_add;
	java_util_ArrayList = static_cast<jclass>(env->NewGlobalRef(env->FindClass("java/util/ArrayList")));
	java_util_ArrayList_ = env->GetMethodID(java_util_ArrayList, "<init>", "(I)V");
	java_util_ArrayList_size = env->GetMethodID(java_util_ArrayList, "size", "()I");
	java_util_ArrayList_get = env->GetMethodID(java_util_ArrayList, "get", "(I)Ljava/lang/Object;");
	java_util_ArrayList_add = env->GetMethodID(java_util_ArrayList, "add", "(Ljava/lang/Object;)Z");
	jclass clazz = (*env).FindClass("java/util/ArrayList");
	jobject obj = (*env).NewObject(clazz, (*env).GetMethodID(clazz, "<init>", "()V"));
	jobject result;
	vector<string> final_data;
	final_data = GetActiveDirectoryUsersData();
	result = env->NewObject(java_util_ArrayList, java_util_ArrayList_, final_data.size());
	for (std::string s : final_data) {
		jstring element = env->NewStringUTF(s.c_str());
		env->CallBooleanMethod(result, java_util_ArrayList_add, element);
		env->DeleteLocalRef(element);
	}
	final_data.clear();
	return result;
}

