#include "StdAfx.h"
#include "JsonTool.h"


JsonTool::JsonTool(void)
{
}


JsonTool::~JsonTool(void)
{
}

/*
功能：
	从Json文件中读取Json数据对象
输入：
	string &strfilePath:文件路径
	Json::Value &root:Json数据（返回）
输出：
	bool:是否读取成功
*/
bool JsonTool::readJsonObject( const string &strfilePath, Json::Value &root, string &err )
{
	bool isSuccess = false;
	if (strfilePath.size() == 0)
	{
		err = "strfilePath is empty!";
		return isSuccess;
	}

	ifstream is(strfilePath, ios::binary);
	if (!is.is_open())
	{
		err = "open json file failed!";
		return isSuccess;
	}

	Json::CharReaderBuilder readerBuilder;

	if (parseFromStream(readerBuilder, is, &root, &err)){

		isSuccess = true;	
	}
	
	is.close();
	return isSuccess;
}

/*
功能：
	保存Json数据对象到Json文件中
输入：
	string &strfilePath:文件路径
	Json::Value &root:Json数据
输出：
	bool:是否读取成功
*/
bool JsonTool::saveJsonObject(const string &strfilePath, const Json::Value &root )
{
	if (strfilePath.size() == 0)
	{
		cout << "strfilePath is empty!" << endl;
		return false;
	}

	ofstream os;
	os.open(strfilePath);
	Json::StreamWriterBuilder writerBuilder;
	const std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
	writer->write(root, &os);
	os.close();

	return true;
}


/*
功能：
	打印Json数据对象
输入：
	Json::Value &root:Json数据
*/
void JsonTool::printJsonObject( const Json::Value &root )
{
	string out = root.toStyledString();
	cout << out << endl;
}
/*
功能：
	将CString数据对象转换为Json数据对象
输入：
	string &str:string数据对象
	Json::Value &root:Json数据对象（返回）
输出：
	是否成功
*/
bool JsonTool::stringToJsonObject( const string &str, Json::Value &root, string &err )
{
	const auto rawJsonLength = static_cast<int>(str.length());

	Json::CharReaderBuilder builder;
	const unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(str.c_str(), str.c_str() + rawJsonLength, &root, &err)) 
	{
		cout << "error" << endl;
		return false;
	}
	return true;
}

/*
功能：
	将Json数据对象转换为CString数据对象
输入：
	Json::Value &root:Json数据对象
	string &str:string数据对象（返回）
*/
void JsonTool::JsonObjectToString( const Json::Value &root, string &str )
{
	str = root.toStyledString();
}

/*
功能：
	从Json文件中读取Json数据对象
输入：
	CString &strfilePath:文件绝对路径
	Json::Value &root:Json数据（返回）
输出：
	bool:是否读取成功
*/
bool JsonTool::readJsonObject( const CString &strfilePath, Json::Value &root )
{
	string err;
	string temp = static_cast<CStringA>(strfilePath);
	return readJsonObject(temp, root, err);
}

/*
功能：
	保存Json数据对象到Json文件中
输入：
	CString &strfilePath:文件路径
	Json::Value &root:Json数据
输出：
	bool:是否读取成功
*/
bool JsonTool::saveJsonObject( const CString &strfilePath, const Json::Value &root )
{
	string temp = static_cast<CStringA>(strfilePath);
	return saveJsonObject(temp, root);
}

/*
功能：
	将CString数据对象转换为Json数据对象
输入：
	CString &str:CString数据对象
	Json::Value &root:Json数据对象（返回）
输出：
	是否成功
*/
bool JsonTool::stringToJsonObject( const CString &str, Json::Value &root )
{
	string err;
	string strTemp = static_cast<CStringA>(str);
	return stringToJsonObject(strTemp, root, err);
}

/*
功能：
	将Json数据对象转换为CString数据对象
输入：
	Json::Value &root:Json数据对象
	CString &str:CString数据对象（返回）
*/
void JsonTool::JsonObjectToString( const Json::Value &root, CString &str )
{
	string temp;
	JsonObjectToString(root, temp);
	str = temp.c_str();
}
