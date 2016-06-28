// PX2ProjectEvent.hpp

#ifndef PX2GRAPHICSEVENTTYPE_HPP
#define PX2GRAPHICSEVENTTYPE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2EventSystem.hpp"

namespace PX2
{

	PX2_DECLARE_EVENT_BEGIN(PX2_ENGINE_ITEM ProjectES)
	PX2_EVENT(NewProject)
	PX2_EVENT(LoadedProject)
	PX2_EVENT(SavedProject)
	PX2_EVENT(CloseProject)
	PX2_EVENT(NewScene)
	PX2_EVENT(SavedScene)
	PX2_EVENT(CloseScene)
	PX2_EVENT(NewUI)
	PX2_EVENT(CloseUI)
	PX2_EVENT(Play)
	PX2_DECLARE_EVENT_END(ProjectES)

}

#endif