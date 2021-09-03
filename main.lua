screens = {}
screens["titlescreen"] = require("screens.titlescreen")
screens["playscreen"] = require("screens.playscreen")
screens["armybuildingscreen"] = require("screens.armybuildingscreen")

soundEffects = {}
soundEffects["button_click"] = love.audio.newSource("sounds/button_click.wav", "static")
soundEffects["button_click2"] = love.audio.newSource("sounds/button_click2.wav", "static")

fonts = {}
fonts["Romulus"] = love.graphics.newFont("fonts/Romulus.ttf", 48)

atlas = love.graphics.newImage("sprites/atlas.png")
atlas:setFilter("linear", "nearest")

function love.load()
	love.window.setMode(800, 600)
	loadScreen("titlescreen")
end

function love.update(dt)
	screens[currentScreen].update(dt)
end

function love.draw()
	-- Reset graphics
	love.graphics.reset()
	love.graphics.setBackgroundColor(1, 1, 1)
	love.graphics.setColor(0, 0, 0)

	-- Call draw
	screens[currentScreen].draw()
end

function love.mousepressed(x, y, button, istouch, presses)
	pcall(screens[currentScreen].mousepressed, x, y, button, istouch, presses)
end

function love.mousereleased(x, y, button, isTouch)
	pcall(screens[currentScreen].mousereleased, x, y, button, istouch)
end

function loadScreen(screen)
	currentScreen = screen
	pcall(screens[currentScreen].load)
end

function getQuad(sprite)
	if sprite == "tank" then
		return love.graphics.newQuad(0, 0, 32, 32, image:getWidth(), image:getHeight())
	end
	if sprite == "city" then
		return love.graphics.newQuad(0, 32, 32, 32, image:getWidth(), image:getHeight())
	end
end
