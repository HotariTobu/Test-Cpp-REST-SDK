#include <Windows.h>
#include <iostream>
#include <cpprest/http_client.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

pplx::task<void> Get()
{
	return pplx::create_task([]
		{
			// proxy����
			// auto config = http_client_config();
			// config.set_proxy(web_proxy(utility::conversions::to_string_t("http://127.0.0.1:8080")));
			// http_client client(L"https://jsonplaceholder.typicode.com/posts/1", config);

			http_client client(L"https://jsonplaceholder.typicode.com/posts/1");
			return client.request(methods::GET);
		}).then([](http_response response)
			{
				if (response.status_code() == status_codes::OK)
				{
					// ���X�|���X�𕶎���Ƃ��Ď擾��A�W���o�͂���
					// auto body = response.extract_string();
					// std::wcout << body.get().c_str() << std::endl;

					// ���X�|���X��JSON�Ƃ��ĉ�͂���
					return response.extract_json();
				}
			}).then([](json::value json)
				{
					// �^�C�g�������擾����
					std::wcout << json[L"title"].as_string() << std::endl;
				});
}

int main()
{
	// �R�}���h�v�����v�g�̕����R�[�h��UTF-8�ɐݒ肷��
	SetConsoleOutputCP(CP_UTF8);

	try
	{
		Get().wait();
	}
	catch (const std::exception & e)
	{
		std::cout << "Error " << e.what() << std::endl;
	}

	return 0;
}