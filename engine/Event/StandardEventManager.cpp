#include "Event/StandardEventManager.h"

namespace pl
{
namespace Event
{
StandardEventManager::StandardEventManager() : mActiveQueue(0)
{
	// Register the wild card event type as soon as the event manager is created.
	EventType wild_card(EventType::WILD_CARD_EVENT_TYPE_STRING);

	mRegisteredTypes.insert(wild_card);
	mListenerMapping[wild_card] = ListenerList();
}

bool StandardEventManager::validateEventType(const EventType& type) const
{
	bool result = false;

	// An empty string will never be valid.
	if (type.getOrigString() != "")
	{
		EventTypeSetQueryResult query = mRegisteredTypes.find(type);

		// An unregistered event type is valid. Or the two event types with the same identifiers must have the same strings.
		if (query == mRegisteredTypes.end() || query->getOrigString() == type.getOrigString())
		{
			result = true;
		}
	}

	return result;
}

void StandardEventManager::queueEvent(const EventSP event)
{
	// Only queues the valid and registered ones. Besides, wild card events are not allowed! Wild card event type is for listeners only!
	if (event.get() != nullptr && event->getType().getIdentifier() != EventType::WILD_CARD_EVENT_TYPE_ID && validateEventType(event->getType())
		&& mRegisteredTypes.find(event->getType()) != mRegisteredTypes.end())
	{
		mQueues[mActiveQueue].push_back(event);
	}
}

bool StandardEventManager::eliminateEvent(const EventType& type, bool all)
{
	bool result = false;

	if (type.getIdentifier() != EventType::WILD_CARD_EVENT_TYPE_ID && validateEventType(type) && mRegisteredTypes.find(type) != mRegisteredTypes.end())
	{
		for (EventQueueQueryResult query = mQueues[mActiveQueue].begin() ; query != mQueues[mActiveQueue].end() ; )
		{
			if ((*query)->getType() == type)
			{
				query = mQueues[mActiveQueue].erase(query);

				if (!result)
				{
					result = true;
				}

				if (!all)
				{
					break;
				}
			}
			else
			{
				++query;
			}
		}
	}

	return result;
}

bool StandardEventManager::dispatch(const clock_t time_limit)
{
	uint8_t inactive_queue = (mActiveQueue + 1) % MAX_QUEUE_NUMBER;
	bool result = true;
	clock_t start_time = clock();

	while (mQueues[inactive_queue].size() > 0)
	{
		EventSP event_query = mQueues[inactive_queue].front();

		if (time_limit != 0 && clock() - start_time > time_limit)
		{
			result = false;
			break;
		}
		else
		{
			// Feed the wild card listeners first.
			ListenerList wild_listeners = mListenerMapping[EventType::WILD_CARD_EVENT_TYPE_STRING];
			ListenerList listeners = mListenerMapping[event_query->getType()];
			bool has_consumed = false;

			for (EventListenerQueryResult wild_card_listener_query = wild_listeners.begin() ; wild_card_listener_query != wild_listeners.end() ; ++wild_card_listener_query)
			{
				// This event is being consumed!
				if ((*wild_card_listener_query)->handleEvent(event_query))
				{
					has_consumed = true;
					break;
				}
			}

			if (!has_consumed)
			{
				for (EventListenerQueryResult listener_query = listeners.begin() ; listener_query != listeners.end() ; ++listener_query)
				{
					// This event is being consumed!
					if ((*listener_query)->handleEvent(event_query))
					{
						break;
					}
				}
			}
		}

		mQueues[inactive_queue].pop_front();
	}

	// Transfers all the un-processed events to the active queue.
	if (!result)
	{
		while (mQueues[inactive_queue].size() > 0)
		{
			mQueues[mActiveQueue].push_front(mQueues[inactive_queue].back());
			mQueues[inactive_queue].pop_back();
		}
	}

	// Exchange the queues.
	mActiveQueue = inactive_queue;

	return result;
}

bool StandardEventManager::triggerEvent(const EventSP event)
{
	bool result = false;

	// Only processes valid events.
	if (event.get() != nullptr && validateEventType(event->getType()) && mRegisteredTypes.find(event->getType()) != mRegisteredTypes.end())
	{
		// Again, feed the wild card listeners first.
		ListenerList wild_card_listeners = mListenerMapping[EventType::WILD_CARD_EVENT_TYPE_STRING];
		ListenerList listeners = mListenerMapping[event->getType()];
			
		for (EventListenerQueryResult wild_card_query = wild_card_listeners.begin() ; wild_card_query != wild_card_listeners.end() ; ++wild_card_query)
		{
			// This event is being consumed!
			if ((*wild_card_query)->handleEvent(event))
			{
				result = true;
				break;
			}
		}

		if (!result)
		{
			for (EventListenerQueryResult query = listeners.begin() ; query != listeners.end() ; ++query)
			{
				// This event is being consumed!
				if ((*query)->handleEvent(event))
				{
					result = true;
					break;
				}
			}
		}
	}

	return result;
}

bool StandardEventManager::registerListener(const EventListenerSP listener)
{
	bool result = false;
	EventType type = listener->getEventType();

	if (validateEventType(type))
	{
		// Registers the event type if it hasn't been registered.
		if (mRegisteredTypes.find(type) == mRegisteredTypes.end())
		{
			mRegisteredTypes.insert(type);
			mListenerMapping[type] = ListenerList();
		}

		ListenerList& listeners = mListenerMapping[type];
		bool is_duplicate = false;

		// In case of duplicate registery...
		for (EventListenerQueryResult query = listeners.begin() ; query != listeners.end() ; ++query)
		{
			if ((*query)->getName() == listener->getName())
			{
				is_duplicate = true;
				break;
			}
		}

		if (!is_duplicate)
		{
			listeners.push_back(listener);
			result = true;
		}
	}

	return result;
}

bool StandardEventManager::unregisterListener(const EventListenerSP listener)
{
	bool result = false;
	EventType type = listener->getEventType();

	// Makes sure the listener to be unregistered is valid and its event type has been registered.
	if (validateEventType(type) && mRegisteredTypes.find(type) != mRegisteredTypes.end())
	{
		// Searches for the listener.
		ListenerList listeners = mListenerMapping[type];
			
		for (EventListenerQueryResult query = listeners.begin() ; query != listeners.end() ; ++query)
		{
			// Yeah, we catched it!
			if ((*query)->getName() == listener->getName())
			{
				result = true;
				listeners.erase(query);
				break;
			}
		}
	}

	return result;
}

StandardEventManager::EventTypeList StandardEventManager::getRegisteredTypes() const
{
	EventTypeList types;
	types.insert(types.begin(), mRegisteredTypes.begin(), mRegisteredTypes.end());

	return types;
}

StandardEventManager::ListenerList StandardEventManager::getRegisteredListeners(const EventType& type) const
{
	if (validateEventType(type) && mRegisteredTypes.find(type) != mRegisteredTypes.end())
	{
		return mListenerMapping.at(type);
	}
	else
	{
		return ListenerList();
	}
}

} // End of namespace Event

} // End of namespace pl