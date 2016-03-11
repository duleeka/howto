#pragma once
#include <stdint.h>
#define MAX_LOG_MSG_LENGTH 4096
enum LogLevel
{
	Debug = 1,
	Verbose,
	Info
};

class RichEditEventLogger
{
public:
	RichEditEventLogger(CRichEditCtrl * logger);
	virtual ~RichEditEventLogger();

public:
	void SetLogLevel(LogLevel logLevel);
	void AddToLog(LogLevel level, const TCHAR * msg, ...);
	void AddToLog(LogLevel level, uint8_t * data, int32_t length, const TCHAR * msg, ...);
	void Clear();
private:
	TCHAR logMsgBuffer[MAX_LOG_MSG_LENGTH];
	CRichEditCtrl * m_Logger;
	LogLevel m_LogLevel;
};

