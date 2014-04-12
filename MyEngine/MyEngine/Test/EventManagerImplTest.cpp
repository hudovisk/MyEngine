/*
 * EventManagerTest.cpp
 *
 *  Created on: Apr 7, 2014
 *      Author: hudo
 */

#include "EventManagerImpl.h"
#include "gtest/gtest.h"

class MockEngineImpl
{
public:
	void onWindowClosed(IEventDataPtr event)
	{

	}
};

class EventManagerImplTest : public ::testing::Test
{
public:
	EventManagerImplTest()
	{
		m_eventManager.init();

		mockEngineDelegator = EventListenerDelegate::from_method<MockEngineImpl,&MockEngineImpl::onWindowClosed>(&mockEngine);
		mockEvent = IEventDataPtr(new WindowClosedEventData(0));
	}

	~EventManagerImplTest()
	{
		m_eventManager.destroy();
	}

	IEventDataPtr mockEvent;
	MockEngineImpl mockEngine;
	EventListenerDelegate mockEngineDelegator;
	EventManagerImpl m_eventManager;
};

TEST_F(EventManagerImplTest, addListennerEmptyList)
{
	bool status = m_eventManager.addListenner(mockEngineDelegator,0);

	ASSERT_EQ(true,status);
}

TEST_F(EventManagerImplTest, addListennerDuplicateListenner)
{
	m_eventManager.addListenner(mockEngineDelegator,0);

	bool status = m_eventManager.addListenner(mockEngineDelegator,0);
	ASSERT_EQ(false,status);
}

TEST_F(EventManagerImplTest, removeListennerEmptyList)
{
	bool status = m_eventManager.removeListenner(mockEngineDelegator,0);

	ASSERT_EQ(false,status);
}

TEST_F(EventManagerImplTest, removeListennerNonEmptyList)
{
	m_eventManager.addListenner(mockEngineDelegator,0);

	bool status = m_eventManager.removeListenner(mockEngineDelegator,0);

	ASSERT_EQ(true,status);
}

TEST_F(EventManagerImplTest, removeListennerNonEmptyListWrongListenner)
{
	m_eventManager.addListenner(mockEngineDelegator,1);

	bool status = m_eventManager.removeListenner(mockEngineDelegator,0);

	ASSERT_EQ(false,status);
}

TEST_F(EventManagerImplTest, queueEventEmptyQueueEmptyDelegatesMap)
{
	bool status = m_eventManager.queueEvent(mockEvent);

	ASSERT_EQ(false,status);
}

TEST_F(EventManagerImplTest, queueEventEmptyQueueNonEmptyDelegatesMap)
{
	m_eventManager.addListenner(mockEngineDelegator,0);

	bool status = m_eventManager.queueEvent(mockEvent);

	ASSERT_EQ(true,status);
}

TEST_F(EventManagerImplTest, queueEventNonEmptyQueueNonEmptyDelegatesMap)
{
	m_eventManager.addListenner(mockEngineDelegator,0);

	m_eventManager.queueEvent(mockEvent);
	bool status = m_eventManager.queueEvent(mockEvent);

	ASSERT_EQ(true,status);
}

TEST_F(EventManagerImplTest, abortEmptyQueueEmptyDelegateList)
{
	bool status = m_eventManager.abortEvent(0);

	ASSERT_EQ(false,status);
}

TEST_F(EventManagerImplTest, abortEmptyQueueNonEmptyDelegateList)
{
	m_eventManager.addListenner(mockEngineDelegator,0);

	bool status = m_eventManager.abortEvent(0);

	ASSERT_EQ(false,status);
}

TEST_F(EventManagerImplTest, abortNonEmptyQueueWrongEventType)
{
	m_eventManager.addListenner(mockEngineDelegator,0);
	m_eventManager.queueEvent(mockEvent);

	bool status = m_eventManager.abortEvent(1);

	ASSERT_EQ(false,status);
}

TEST_F(EventManagerImplTest, abortNonEmptyQueueCorrectEventType)
{
	m_eventManager.addListenner(mockEngineDelegator,0);
	m_eventManager.queueEvent(mockEvent);

	bool status = m_eventManager.abortEvent(0);

	ASSERT_EQ(true,status);
}

TEST_F(EventManagerImplTest, triggerEventEmptyDelegates)
{
	bool status = m_eventManager.triggerEvent(mockEvent);

	ASSERT_EQ(false, status);
}

TEST_F(EventManagerImplTest, triggerEventNonEmptyDelegatesWrongType)
{
	m_eventManager.addListenner(mockEngineDelegator,1);
	bool status = m_eventManager.triggerEvent(mockEvent);

	ASSERT_EQ(false, status);
}

TEST_F(EventManagerImplTest, triggerEventNonEmptyDelegates)
{
	m_eventManager.addListenner(mockEngineDelegator,0);
	bool status = m_eventManager.triggerEvent(mockEvent);

	ASSERT_EQ(true, status);
}
