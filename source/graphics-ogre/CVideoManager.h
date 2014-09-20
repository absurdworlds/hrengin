/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CVideoManager_
#define _hrengin_CVideoManager_

#include <vector>

#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/gui/IGUIManager.h>
#include <hrengin/graphics/ISceneManager.h>
#include <hrengin/graphics/IRenderingDevice.h>

#include "CVisNode.h"

namespace Ogre {
class Root;
class RenderWindow;
}

namespace hrengin {
namespace gui {
class CGUIManager;
}

namespace graphics {

class CVisNode;

class CVideoManager : public IVideoManager {
friend class CGUIManager;
public:
	CVideoManager(core::ISettingsManager* settings);
	virtual ~CVideoManager();
	
	virtual bool step();
	virtual void wait();

	virtual bool isWindowActive();
	

	virtual IRenderingDevice* getRenderingDevice() const;
	virtual ISceneManager* getSceneManager() const;
	virtual gui::IGUIManager* getGUIManager() const;

	//virtual IMesh* loadMesh(const char * modelname);
	virtual u32 getTime();
protected:
	// Configure video manager and yada
	void configure(core::ISettingsManager* settings);
	void setWindow(core::ISettingsManager* settings);
private:
	Ogre::Root* ogreRoot_;
	Ogre::RenderWindow* window_;

	ISceneManager* sceneManager_;
	IRenderingDevice* renderer_;
	gui::IGUIManager* guiManager_;
};
	
} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CVideoManager_