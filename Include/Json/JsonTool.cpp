#include "StdAfx.h"
#include "JsonTool.h"


JsonTool::JsonTool(void)
{
}


JsonTool::~JsonTool(void)
{
}

/*
���ܣ�
	��Json�ļ��ж�ȡJson���ݶ���
���룺
	string &strfilePath:�ļ�·��
	Json::Value &root:Json���ݣ����أ�
�����
	bool:�Ƿ��ȡ�ɹ�
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
���ܣ�
	����Json���ݶ���Json�ļ���
���룺
	string &strfilePath:�ļ�·��
	Json::Value &root:Json����
�����
	bool:�Ƿ��ȡ�ɹ�
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
���ܣ�
	��ӡJson���ݶ���
���룺
	Json::Value &root:Json����
*/
void JsonTool::printJsonObject( const Json::Value &root )
{
	string out = root.toStyledString();
	cout << out << endl;
}
/*
���ܣ�
	��CString���ݶ���ת��ΪJson���ݶ���
���룺
	string &str:string���ݶ���
	Json::Value &root:Json���ݶ��󣨷��أ�
�����
	�Ƿ�ɹ�
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
���ܣ�
	��Json���ݶ���ת��ΪCString���ݶ���
���룺
	Json::Value &root:Json���ݶ���
	string &str:string���ݶ��󣨷��أ�
*/
void JsonTool::JsonObjectToString( const Json::Value &root, string &str )
{
	str = root.toStyledString();
}

/*
���ܣ�
	��Json�ļ��ж�ȡJson���ݶ���
���룺
	CString &strfilePath:�ļ�����·��
	Json::Value &root:Json���ݣ����أ�
�����
	bool:�Ƿ��ȡ�ɹ�
*/
bool JsonTool::readJsonObject( const CString &strfilePath, Json::Value &root )
{
	string err;
	string temp = static_cast<CStringA>(strfilePath);
	return readJsonObject(temp, root, err);
}

/*
���ܣ�
	����Json���ݶ���Json�ļ���
���룺
	CString &strfilePath:�ļ�·��
	Json::Value &root:Json����
�����
	bool:�Ƿ��ȡ�ɹ�
*/
bool JsonTool::saveJsonObject( const CString &strfilePath, const Json::Value &root )
{
	string temp = static_cast<CStringA>(strfilePath);
	return saveJsonObject(temp, root);
}

/*
���ܣ�
	��CString���ݶ���ת��ΪJson���ݶ���
���룺
	CString &str:CString���ݶ���
	Json::Value &root:Json���ݶ��󣨷��أ�
�����
	�Ƿ�ɹ�
*/
bool JsonTool::stringToJsonObject( const CString &str, Json::Value &root )
{
	string err;
	string strTemp = static_cast<CStringA>(str);
	return stringToJsonObject(strTemp, root, err);
}

/*
���ܣ�
	��Json���ݶ���ת��ΪCString���ݶ���
���룺
	Json::Value &root:Json���ݶ���
	CString &str:CString���ݶ��󣨷��أ�
*/
void JsonTool::JsonObjectToString( const Json::Value &root, CString &str )
{
	string temp;
	JsonObjectToString(root, temp);
	str = temp.c_str();
}
