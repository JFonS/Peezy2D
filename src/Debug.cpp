#include <SFML/Graphics.hpp>

#include "include/Debug.hpp"

using namespace sf;

string Debug::logFile;
ofstream Debug::fileStream;
unsigned char Debug::fileMode = CZ_DBG_LOG | CZ_DBG_WRN | CZ_DBG_ERR;
unsigned char Debug::outputMode = CZ_DBG_FILE | CZ_DBG_TERM;

void Debug::Log(ostringstream &log) 
{
    if (outputMode & CZ_DBG_FILE and fileMode & CZ_DBG_LOG)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & CZ_DBG_TERM) 
    {
    	cout << log.str();
	}
}

void Debug::Warning(ostringstream &log) 
{
    if (outputMode & CZ_DBG_FILE and fileMode & CZ_DBG_WRN)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & CZ_DBG_TERM) 
    {
    	cerr << log.str();
    }
}

void Debug::Error(ostringstream &log) 
{
    if (outputMode & CZ_DBG_FILE and fileMode & CZ_DBG_ERR)
	{
        if (fileStream.is_open()) fileStream << log.str(); 
    }

    if (outputMode & CZ_DBG_TERM) 
    {
    	cerr << log.str();
    }
}

void Debug::SetFile(string filepath) 
{
	if (filepath == CZ_AUTO_LOG_FILE) 
	{
		string dbg = CZ_LOG_DIR;
		dbg.append("/");
		dbg.append("my-log-file");
		dbg.append(".log");
		filepath = dbg;
		cerr << "Saving log to: " << filepath << endl;
	}
	logFile = filepath;
	if (fileStream.is_open()) fileStream.close();
        fileStream.open(logFile,fstream::out);
}


ostream& operator<<(ostream &log, const Vector2i &v)
{
    log << "(" << v.x << ", " << v.y << ")";
    return log;
}

ostream& operator<<(ostream &log, const Vector2f &v)
{
    log << "(" << v.x << ", " << v.y << ")";
    return log;
}
