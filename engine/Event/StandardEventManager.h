#ifndef PL_EVENT_STANDARD_EVENT_MANAGER
#define PL_EVENT_STANDARD_EVENT_MANAGER

#include "Core/Config.h"
#include "Event/IEventManager.h"

#include <vector>
#include <map>
#include <set>
#include <list>

using namespace std;

namespace Prelude
{
namespace Event
{
/**
  * A default implementation for IEventManager that uses two queues taking turns to process events, a set to hold event types and a map to map event types to lists of listeners.
  */
class PRELUDE_ENGINE StandardEventManager : implements IEventManager
{
public:
	typedef vector<EventType> EventTypeList;
	typedef vector<EventListenerSP> ListenerList;
	typedef EventTypeList::iterator EventTypeListQueryResult;
	typedef ListenerList::iterator EventListenerQueryResult;

	/**
	  * The constructor that gets the wild card event type registered as soon as the event manager gets constructed.
	  */
	StandardEventManager();

	/**
	  * @see IEventManager
	  */
	bool validateEventType(const EventType& type) const;

	/**
	  * @see IEventManager
	  */
	void queueEvent(const EventSP event);

	/**
	  * @see IEventManager
	  */
	bool eliminateEvent(const EventType& type, bool all = false);

	/**
	  * @see IEventManager
	  */
	bool dispatch(const clock_t time_limit = 0);

	/**
	  * @see IEventManager
	  */
	bool triggerEvent(const EventSP event);

	/**
	  * @see IEventManager
	  */
	bool registerListener(const EventListenerSP listener);

	/**
	  * @see IEventManager
	  */
	bool unregisterListener(const EventListenerSP listener);

	/**
	  * Returns all the registered event types.
	  * @returns All the event types registered to this event manager.
	  */
	EventTypeList getRegisteredTypes() const;

	/**
	  * Returns all the registered event listeners that listen to a given event type.
	  * @param type The type for searching.
	  * @returns All the event listeners registered to this event manager that listen to a given event type. Returns an empty list if the given type is invalid or there is no listener interested in it.
	  */
	ListenerList getRegisteredListeners(const EventType& type) const;

private:
	typedef set<EventType> EventTypeSet;
	typedef map<EventType, ListenerList> EventListenerMapping;
	typedef list<EventSP> EventQueue;
	typedef EventTypeSet::iterator EventTypeSetQueryResult;
	typedef EventQueue::iterator EventQueueQueryResult;
		
	static const uint8_t MAX_QUEUE_NUMBER = 2;                   //!< The maximal number of the event queues.

	EventQueue mQueues[MAX_QUEUE_NUMBER];                        //!< The event queues.
	EventTypeSet mRegisteredTypes;                               //!< The registered event types.
	EventListenerMapping mListenerMapping;                       //!< The mapping from event types to event listeners.

	uint8_t mActiveQueue;                                        //!< The index of the current active event queue. An event queue is active when it receives incoming events.
};

} // End of namespace Event

} // End of namespace Prelude

#endif