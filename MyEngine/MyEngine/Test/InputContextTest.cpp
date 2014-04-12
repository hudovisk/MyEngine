/*
 * InputContextTest.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: hudo
 */

#include "InputContext.h"
#include "gtest/gtest.h"

class InputContextTest : public ::testing::Test
{
protected:
	// Per-test-case set-up.
	// Called before the first test in this test case.
	// Can be omitted if not needed.
	static void SetUpTestCase() {
		inputContext.init("inputTest.xml");
	}

	// Per-test-case tear-down.
	// Called after the last test in this test case.
	// Can be omitted if not needed.
	static void TearDownTestCase() {

	}

	// You can define per-test set-up and tear-down logic as usual.
	virtual void SetUp() {

	}
	virtual void TearDown() {

	}

	static InputContext inputContext;
};

InputContext InputContextTest::inputContext;

TEST_F(InputContextTest, initWrongFile)
{
	ASSERT_DEATH(inputContext.init("wrongFile.xml");,"InputContext init file: .* error, possibly wrong file or bad XML");
}

TEST_F(InputContextTest, initCorrectFile)
{
	bool status = inputContext.init("inputTest.xml");

	ASSERT_EQ(true, status);
}

TEST_F(InputContextTest, parseEmptyInput)
{
	std::list<InputEvent> inputList;
	std::vector<InputMessage> messages = inputContext.parse(inputList);

	ASSERT_EQ(true, messages.empty());
}

TEST_F(InputContextTest, parseNonEmptyInputWrongInput)
{
	std::list<InputEvent> inputList;

	InputEvent wrongInput(0);
	inputList.push_back(wrongInput);
	std::vector<InputMessage> messages = inputContext.parse(inputList);

	ASSERT_EQ(true, messages.empty());
}

TEST_F(InputContextTest, parseNonEmptyInputCorrectKeyInput)
{
	std::list<InputEvent> inputList;

	InputEvent correctKeyInput(0);
	correctKeyInput.m_type = InputEventType::KEYBOARD;
	correctKeyInput.m_key.m_code = SDLK_w;
	correctKeyInput.m_key.m_pressed = true;

	inputList.push_back(correctKeyInput);
	std::vector<InputMessage> messages = inputContext.parse(inputList);

	InputMessage message = messages.at(0);

	ASSERT_EQ(message.id, 1);
}

TEST_F(InputContextTest, parseNonEmptyInputCorrectMouseInput)
{
	std::list<InputEvent> inputList;

	InputEvent correctMouseInput(0);
	correctMouseInput.m_type = InputEventType::MOUSE;
	correctMouseInput.m_mouse.m_code = MOUSE_MOTION;
	correctMouseInput.m_mouse.m_posX = 100;
	correctMouseInput.m_mouse.m_posY = 200;
	correctMouseInput.m_mouse.m_pressed = false;

	inputList.push_back(correctMouseInput);
	std::vector<InputMessage> messages = inputContext.parse(inputList);

	InputMessage message = messages.at(0);

	ASSERT_EQ(message.id, 3);
	ASSERT_EQ(message.pos[0], 100);
	ASSERT_EQ(message.pos[1], -200);
}

TEST_F(InputContextTest, parseNonEmptyInputCorrectKeyAndMouseInput)
{
	std::list<InputEvent> inputList;

	InputEvent correctKeyInput(0);
	correctKeyInput.m_type = InputEventType::KEYBOARD;
	correctKeyInput.m_key.m_code = SDLK_w;
	correctKeyInput.m_key.m_pressed = true;

	InputEvent correctMouseInput(0);
	correctMouseInput.m_type = InputEventType::MOUSE;
	correctMouseInput.m_mouse.m_code = MOUSE_MOTION;
	correctMouseInput.m_mouse.m_posX = 100;
	correctMouseInput.m_mouse.m_posY = 200;
	correctMouseInput.m_mouse.m_pressed = false;

	inputList.push_back(correctKeyInput);
	inputList.push_back(correctMouseInput);
	std::vector<InputMessage> messages = inputContext.parse(inputList);

	InputMessage message = messages.at(0);

	ASSERT_EQ(message.id, 1);

	message = messages.at(1);

	ASSERT_EQ(message.id, 3);
	ASSERT_EQ(message.pos[0], 100);
	ASSERT_EQ(message.pos[1], -200);
}





