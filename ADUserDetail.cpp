#include <objbase.h>
#include <wchar.h>
#include <activeds.h>
#include <Windows.h>
#include "atltime.h"
#include <sddl.h>
#include <iostream>
#include <string>
#include<vector>
#include <string>
#include <comutil.h>
#include "ADUserDetail.h"
using namespace std;

extern int arr[5] = { 0 };

int IS_BUFFER_ENOUGH(UINT maxAlloc, LPWSTR pszTarget, LPCWSTR pszSource, int toCopy = -1);

int calculatedifference(SYSTEMTIME expdate);

char* convertDatetoString(VARIANT varDate2);

vector<string> GetActiveDirectoryUsersData()
{
	string data;
	vector<string> list1;
	const string content[20];
	int maxAlloc = MAX_PATH * 2;
	LPOLESTR pszBuffer = new OLECHAR[maxAlloc];
	wcscpy_s(pszBuffer, maxAlloc, L"");
	BOOL bReturnVerbose = TRUE;

	//authentication to user
	CoInitialize(NULL);
	HRESULT hr = S_OK;
	//Get rootDSE and the current user's domain container DN.
	IADs* pObject = NULL;
	IDirectorySearch* pContainerToSearch = NULL;
	LPOLESTR szPath = new OLECHAR[MAX_PATH];
	VARIANT var;
	hr = ADsOpenObject(L"LDAP://rootDSE",
		NULL,
		NULL,
		ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
		IID_IADs,
		(void**)&pObject);
	if (FAILED(hr))
	{
		if (pObject)
			pObject->Release();
		delete[] pszBuffer;
		delete[] szPath;
		CoUninitialize();
		data = "Could not execute query.Could not bind to LDAP ://rootDSE.";
	}
	if (SUCCEEDED(hr))
	{
		hr = pObject->Get((BSTR)L"defaultNamingContext", &var);
		if (SUCCEEDED(hr))
		{
			//Build path to the domain container.
			wcscpy_s(szPath, MAX_PATH, L"LDAP://");
			if (IS_BUFFER_ENOUGH(MAX_PATH, szPath, var.bstrVal) > 0)
			{
				wcscat_s(szPath, MAX_PATH, var.bstrVal);
			}
			else
			{
				delete[] pszBuffer;
				delete[] szPath;
				CoUninitialize();
				data = "Buffer is too small for the domain DN";

			}
			hr = ADsOpenObject(szPath,
				NULL,
				NULL,
				ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
				IID_IDirectorySearch,
				(void**)&pContainerToSearch);

			if (SUCCEEDED(hr))
			{
				//additional addon
				if (!pContainerToSearch)
				{

					data = "could not fetch data.Out of Memory";
				}
				//Create search filter
				LPOLESTR pszSearchFilter = new OLECHAR[MAX_PATH * 2];
				if (!pszSearchFilter)
				{
					//return E_OUTOFMEMORY;
					data = "Could not Fetch data.Out of Memory";
				}
				wchar_t szFormat[] = L"(&(objectClass=user)(objectCategory=person)%s)";// common query which includes all users
				if (IS_BUFFER_ENOUGH(MAX_PATH * 2, szFormat, pszBuffer) > 0)
				{
					//Add the filter.
					swprintf_s(pszSearchFilter, MAX_PATH * 2, szFormat, pszBuffer);
				}
				else
				{
					delete[] pszSearchFilter;
					data = "The filter is too large for buffer, aborting...";
				}
				//Specify subtree search
				ADS_SEARCHPREF_INFO SearchPrefs;
				SearchPrefs.dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
				SearchPrefs.vValue.dwType = ADSTYPE_INTEGER;
				SearchPrefs.vValue.Integer = ADS_SCOPE_SUBTREE;
				DWORD dwNumPrefs = 1;

				// COL for iterations
				LPOLESTR pszColumn = NULL;
				ADS_SEARCH_COLUMN col;
				HRESULT hr;

				// Interface Pointers
				IADs* pObj = NULL;
				IADs* pIADs = NULL;

				// Handle used for searching
				ADS_SEARCH_HANDLE hSearch = NULL;

				// Set the search preference
				hr = pContainerToSearch->SetSearchPreference(&SearchPrefs, dwNumPrefs);
				if (FAILED(hr))
				{
					delete[] pszSearchFilter;
					//return hr; should change return type
				}

				SYSTEMTIME systemtime;
				DATE date;

				LPOLESTR szName = new OLECHAR[MAX_PATH];
				LPOLESTR szDN = new OLECHAR[MAX_PATH];
				if (!szName || !szDN)
				{
					delete[] pszSearchFilter;
					if (szDN)
						delete[] szDN;
					if (szName)
						delete[] szName;
				}

				int iCount = 0;
				int innercolumn = 0;
				DWORD x = 0L;
				hr = pContainerToSearch->ExecuteSearch(pszSearchFilter,
					NULL,
					-1L,
					&hSearch);
				if (SUCCEEDED(hr))
				{
					hr = pContainerToSearch->GetFirstRow(hSearch);
					if (SUCCEEDED(hr))
					{
						int outeriter = 0, inneriter = 0;

						while (hr != S_ADS_NOMORE_ROWS)
						{
							int iter = 0;
							vector<string> list2;
							//list2.push_back("[+] Personal Data");
							//Keep track of count.
							iCount++;
							if (bReturnVerbose)
							// loop through the array of passed column names,
							// print the data for each column

							while (pContainerToSearch->GetNextColumnName(hSearch, &pszColumn) != S_ADS_NOMORE_COLUMNS)
							{
								hr = pContainerToSearch->GetColumn(hSearch, pszColumn, &col);
								if (SUCCEEDED(hr))
								{
									// Print the data for the column and free the column
									if (bReturnVerbose)
									{
										switch (col.dwADsType)
										{
										case ADSTYPE_CASE_EXACT_STRING:
										case ADSTYPE_CASE_IGNORE_STRING:
										case ADSTYPE_PRINTABLE_STRING:
										case ADSTYPE_NUMERIC_STRING:
										case ADSTYPE_TYPEDNAME:
										case ADSTYPE_FAXNUMBER:
										case ADSTYPE_PATH:
										case ADSTYPE_OBJECT_CLASS:

											for (x = 0; x < col.dwNumValues; x++)
											{
												iter = iter + 1;
												char* st = _com_util::ConvertBSTRToString(col.pADsValues[x].CaseIgnoreString);
												if (iter == 5)
												{
													list2.push_back(st);
												}
												if (wcscmp(L"ADsPath", col.pszAttrName) == 0)
												{

													IADsUser* pUser;
													SYSTEMTIME ExpirationDate;


													hr = ADsGetObject(col.pADsValues[x].CaseIgnoreString, IID_IADsUser, (void**)&pUser);
													if (SUCCEEDED(hr))
													{
														//password expiration date
														DATE expirationDate;
														VARIANT varDate;
														hr = pUser->get_PasswordExpirationDate(&expirationDate);
														SYSTEMTIME PasswordExpirationDate;
														VariantTimeToSystemTime(expirationDate, &PasswordExpirationDate);
														list2.push_back("[+] Password expire settings:");
														if (SUCCEEDED(hr))
														{
															varDate.vt = VT_DATE;
															varDate.date = expirationDate;
															VariantChangeType(&varDate, &varDate, VARIANT_NOVALUEPROP, VT_BSTR);

															VariantTimeToSystemTime(expirationDate, &ExpirationDate);

															if (ExpirationDate.wYear == 1970) {
																list2.push_back("password never expires");
															}
															else if (ExpirationDate.wYear == 1899)
															{
																list2.push_back("User must change password at next login");
															}
															else if (ExpirationDate.wYear > 1970)
															{
																calculatedifference(PasswordExpirationDate);
																int* q = arr;
																if (q[0] < 0 || q[1] < 0 || q[2] < 0)
																{
																	string st;
																	if (q[0] == 0 && q[2] != 0)
																	{
																		list2.push_back("    Password Expired " + to_string(0) + " days " + to_string(0 - q[2]) + " hours " + to_string(0 - q[1]) + " minutes ago");
																	}
																	else if (q[0] != 0 && q[2] == 0)
																	{
																		list2.push_back("    Password Expired " + to_string(0 - q[0]) + " days " + to_string(0) + " hours " + to_string(0 - q[1]) + " minutes ago");
																	}
																	else if (q[0] == 0 && q[2] == 0)
																	{
																		list2.push_back("    Password Expired " + to_string(0) + " days " + to_string(0) + " hours " + to_string(0 - q[1]) + " minutes ago");
																	}
																	else
																	{
																		list2.push_back("    Password Expired " + to_string(0 - q[0]) + " days " + to_string(0 - q[2]) + " hours " + to_string(0 - q[1]) + " minutes ago");

																	}
																	list2.push_back(convertDatetoString(varDate));
																	VariantClear(&varDate);
																}
																else {
																	list2.push_back("Password will expire in " + to_string(q[0]) + " days " + to_string(q[2]) + " hours " + to_string(q[1]) + " minutes");
																	list2.push_back(convertDatetoString(varDate));
																	VariantClear(&varDate);
																}
															}
														}
														// Account enabled or disabled
														list2.push_back("[+] Account Enabled/Disabled : ");
														VARIANT_BOOL pfAccountDisabled;
														hr = pUser->get_AccountDisabled(&pfAccountDisabled);
														if (SUCCEEDED(hr))
															if (pfAccountDisabled != 0) {
																list2.push_back("account disabled");
															}
															else if (pfAccountDisabled == 0) {
																list2.push_back("account enabled");
															}

														//bad logon count
														list2.push_back("[+] BadLogonCount : ");
														LONG get_BadLogincount;
														hr = pUser->get_BadLoginCount(&get_BadLogincount);
														list2.push_back(to_string(get_BadLogincount));

														//passowrd last changed
														list2.push_back("[+] PasswordLastChanged : ");
														DATE pswdlastchange;
														VARIANT varDate1;
														hr = pUser->get_PasswordLastChanged(&pswdlastchange);
														if (SUCCEEDED(hr))
														{
															varDate1.vt = VT_DATE;
															varDate1.date = pswdlastchange;
															VariantChangeType(&varDate1, &varDate1, VARIANT_NOVALUEPROP, VT_BSTR);
															list2.push_back((string)convertDatetoString(varDate1));
															VariantClear(&varDate1);
														}
														else
														{
															list2.push_back("Haven't changed the password from the created date");

														}
														//ACCOUNT EXPIRATION DATE
														list2.push_back("[+] Account Expiry Details : ");
														DATE accexpirationDate;
														hr = pUser->get_AccountExpirationDate(&accexpirationDate);
														if (SUCCEEDED(hr))
														{
															// additional details
															varDate.vt = VT_DATE;
															varDate.date = accexpirationDate;
															VariantChangeType(&varDate, &varDate, VARIANT_NOVALUEPROP, VT_BSTR);
															SYSTEMTIME ExpirationDate;
															VariantTimeToSystemTime(accexpirationDate, &ExpirationDate);
															if (ExpirationDate.wYear == 1970)
															{
																list2.push_back("Account Never Expires");
															}
															else
															{
																calculatedifference(ExpirationDate);
																int* p = arr;
																if (p[1] < 0 || p[2] < 0 || p[3] < 0)
																{
																	if (p[0] == 0 && p[2] != 0)
																	{
																		list2.push_back(" Account Expired " + to_string(0) + " days " + to_string(0 - p[2]) + " hours " + to_string(0 - p[1]) + " minutes ago");
																	}
																	else if (p[0] != 0 && p[2] == 0)
																	{
																		list2.push_back("Account Expired " + to_string(0 - p[0]) + " days " + to_string(0) + " hours " + to_string(0 - p[1]) + " minutes ago");
																	}
																	else if (p[0] == 0 && p[2] == 0)
																	{
																		list2.push_back("Account Expired " + to_string(0) + " days " + to_string(0) + " hours " + to_string(0 - p[1]) + " minutes ago");
																	}
																	else
																	{
																		list2.push_back("Account Expired " + to_string(0 - p[0]) + " days " + to_string(0 - p[2]) + " hours " + to_string(0 - p[1]) + " minutes ago");
																	}
																}
																else
																{
																	list2.push_back(convertDatetoString(varDate));
																}
															}
															VariantClear(&varDate);
														}

														//last failed login
														list2.push_back("[+] LastFailedLogin : ");
														DATE lastfailedlogin;
														VARIANT varDate3;
														hr = pUser->get_LastFailedLogin(&lastfailedlogin);
														if (SUCCEEDED(hr))
														{
															varDate3.vt = VT_DATE;
															varDate3.date = lastfailedlogin;
															VariantChangeType(&varDate3, &varDate3, VARIANT_NOVALUEPROP, VT_BSTR);
															list2.push_back(convertDatetoString(varDate3));
															VariantClear(&varDate3);
														}
														else
														{
															list2.push_back("Haven't Logined After account created");
														}

														//account locked or not
														list2.push_back("[+] LOCK_STATUS :");
														VARIANT_BOOL isaccountlocked;
														hr = pUser->get_IsAccountLocked(&isaccountlocked);
														if (isaccountlocked == 0)
														{
															list2.push_back("Not locked");
														}
														else
														{
															list2.push_back("locked");
														}
														pUser->Release();
													}
												}
											}
										}
									}
									pContainerToSearch->FreeColumn(&col);
								}
								FreeADsMem(pszColumn);
							}
							inneriter = 0;
							++outeriter;
							string data1;
							for (int i = 0; i < list2.size(); i++) {
								data1 = data1 + (list2[i]);
								data1 = data1 + "\n";
							}
							list1.push_back(data1);
							hr = pContainerToSearch->GetNextRow(hSearch);
						}
					}
					// Close the search handle to clean up
					pContainerToSearch->CloseSearchHandle(hSearch);
				}
				return list1;

				if (SUCCEEDED(hr) && 0 == iCount)
					hr = S_FALSE;
				delete[] pszSearchFilter;
				delete[] szName;
				delete[] szDN;
				if (SUCCEEDED(hr))
				{
					if (S_FALSE == hr)
					data = "No user object could be found.";

				}
				else if (0x8007203e == hr)
				{
					data = "Could not execute query. An invalid filter was specified.";
				}
				else
				{
					data = "Query failed to run.HRESULT: " + hr;
				}
			}
			else
			{
				data = "Could not execute query. Could not bind to the container.";
			}
			if (pContainerToSearch)
				pContainerToSearch->Release();
		}
		VariantClear(&var);
	}
	if (pObject)
		pObject->Release();

	delete[] pszBuffer;
	delete[] szPath;

	// Uninitialize COM
	CoUninitialize();
	return list1;
}
int IS_BUFFER_ENOUGH(UINT maxAlloc, LPWSTR pszTarget, LPCWSTR pszSource, int toCopy)

{
	if (toCopy == -1)
	{
		toCopy = wcslen(pszSource);
	}
	return maxAlloc - (wcslen(pszTarget) + toCopy + 1);
}
int calculatedifference(SYSTEMTIME expdate)
{
	time_t rawtime = time(0);
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	int yr = timeinfo.tm_year + 1900;
	int mn = timeinfo.tm_mon + 1;
	CTime t1(expdate.wYear, expdate.wMonth, expdate.wDay, expdate.wHour, expdate.wMinute, expdate.wSecond);
	CTime t2(yr, mn, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
	CTimeSpan ts = t1 - t2;
	int daydifference = ts.GetDays();
	int mindifference = ts.GetMinutes();
	int hrdifference = ts.GetHours();
	int di = ts.GetTotalHours();
	arr[0] = daydifference;
	arr[1] = mindifference;
	arr[2] = hrdifference;
	return 0;
}
char* convertDatetoString(VARIANT varDate2)
{
	char* lpszText2 = _com_util::ConvertBSTRToString(varDate2.bstrVal);
	return lpszText2;
}