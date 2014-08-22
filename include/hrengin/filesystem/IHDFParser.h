#ifndef _hrengin_IHndfParser_
#define _hrengin_IHndfParser_

#include <hrengin/common/hrenginapi.h>

#include <hrengin/common/Vector3d.h>

#include <string>

namespace hrengin {
namespace io {

class IReadFile;

/* Enumeration for objects parsed by HDF parser. */
enum HdfObjectType {
	HDF_OBJ_NULL = 0,
	HDF_OBJ_NODE,
	HDF_OBJ_NODE_END,
	HDF_OBJ_VAL,
	HDF_OBJ_CMD
};

/* Enumeration for parser log messages */
enum HdfParserMessage {
	HDF_ERR_NOTICE,
	HDF_ERR_WARNING,
	HDF_ERR_ERROR
};

/* 
# HDF parser
## Description
Interface for reading hrengin's HDF files. This parser provides a read-only access to documents in HDF 1.1.1 format.

It can read only in forward mode, it is not able to rewind. The design goal of this parser is to quickly read HDF document without usage of any intermediate data structures.

## Usage
To create a HDF parser use a factory function
	IHDFParser* createHDFParser(IReadFile* file);

The code below provides an example of reading this structure:
	
	!hdf_version "1.1.1"
	[msg [color 
		red = 100
		blue = 200
		green = 200]
		text = "Starting the endine"]
	[msg [color 
		red = 80
		blue = 80
		green = 240]
		text = "Success!"]
	[msg [color 
		red = 80
		green = 80
		blue = 240]
		text = "Reading config..."]

### Example code
	#include <string>
	#include <vector>

	#include <hrengin/platform/IReadFile.h>
	#include <hrengin/core/IHDFParser.h>

	using namespace hrengin;
	using namespace io;

	// the struct representing a message
	struct Message {
		struct color {
			u8 red;
			u8 green;
			u8 blue;
		} color;
		std::string text;
	};

	// function to for parsing a single node
	void parseNode(IHDFParser* hdf, std::string node, Message& msg) 
	{
		// any object must be read strictly in this order
		while(hdf->read()) {
			HdfObjectType type = hdf->getObjectType();
			std::string name = hdf->getObjectName();

			switch(type) {
			case HDF_OBJ_NODE: // recursively parse a subnode
				void parseNode(hdf, name, msg);
			case HDF_OBJ_VAL: // parse and store a variable 
				if(name == "red" && node == "color") {
					hdf->readInt(msg.color.red);
				} else if(name == "blue" && node == "color") {
					hdf->readInt(msg.color.red);
				} else if(name == "green" && node == "color") {
					hdf->readInt(msg.color.red);
				} else if(name == "text" && node == "msg") {
					hdf->readString(msg.text);
				} else {
					hdf->error(HDF_ERR_ERROR, "unknown object: " + name);
				}
			case HDF_OBJ_NODE_END: // reached an end of node - exit
				break;
			case HDF_OBJ_NULL:
			default:
				return;
			}
		}
	}

	void main()
	{
		// open the file and parser
		IReadFile* file = openReadFile("file.hdf");
		IHDFParser* hdf = createHDFParser(file);

		std::vector<Message> msgLog;

		// parse the file until end is reached

		while(hdf->read()) {
			if(hdf->getObjectType() == HDF_OBJ_NODE)) {
				std::string name = hdf->getObjectName();

				// skip unknown node
				if(name != "msg") {
					hdf->warning(HDF_ERR_ERROR, "unknown node: " + name);
					hdf->skipNode();
				}

				Message msg;
				void parseNode(hdf, hdf->getObjectName(), msg);

				msgLog.push_back(msg);
			} else {
				break;
			}
		}

		delete hdf;
		delete file;
	}
*/
class IHDFParser
{
public:
	/* fast-forward to the next object */
	virtual bool read() = 0;

	/* read the object's type
	   return: the object type or 0 (HDF_OBJ_NULL) in case of failure */
	virtual HdfObjectType getObjectType() = 0;
	
	/* read the object's name
	   arg name: output of the function
	   return: name of the object or empty string in case of failure */
	virtual void getObjectName(std::string& name) = 0;

	/* read the value of the variable
	   param val: output of the function
	   return: formatted value */
	virtual void readFloat(float& val) = 0;
	virtual void readFloat(double& val) = 0;
	virtual void readInt(u32& val) = 0;
	virtual void readInt(i32& val) = 0;
	virtual void readBool(bool& val) = 0;
	virtual void readString(std::string& val) = 0;
	virtual void readVector3d(Vector3d& val) = 0;

	/* skip current value or node (with all subnodes) */
	virtual void skipValue() = 0;
	virtual void skipNode() = 0;

	/* add message to the parser's error log
	   HDF_ERR_NOTICE � an unimportant message
	   HDF_ERR_WARNING � warning, non-critical error
	   HDF_ERR_ERROR ��critical error, stops the parsing*/
	virtual void error(HdfParserMessage type, std::string msg) = 0;
};

/* Creates an instance of HDF parser */
HRENGINFILESYSTEM_API IHDFParser* createHDFParser(IReadFile* file);


}
}


#endif//_hrengin_IHndfParser_