/*
	作者：王峰(2020.10.2)
	功能：
		Json工具类
	目的：
		封装json文件存取方法
	修改时间：2020.10.3 
	修改内容：将string与CString方法分开
	测试时间：2020.11.3
*/
#pragma once

#include "json.h"
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
using namespace std;

class JsonTool
{
public:
	JsonTool(void);
	~JsonTool(void);

	static bool readJsonObject(const CString &strfilePath, Json::Value &root);
	static bool saveJsonObject(const CString &strfilePath, const Json::Value &root);
	static bool stringToJsonObject(const CString &str, Json::Value &root);
	static void JsonObjectToString(const Json::Value &root, CString &str);
	static void printJsonObject(const Json::Value &root);
	

	static bool readJsonObject(const string &strfilePath, Json::Value &root, string &err);
	static bool saveJsonObject(const string &strfilePath, const Json::Value &root);
	static bool stringToJsonObject(const string &str, Json::Value &root, string &err);
	static void JsonObjectToString(const Json::Value &root, string &str);
};

