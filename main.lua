function love.load()
	-- Set window mode
	love.window.setMode(800, 600)

	-- Load screens
	screens = {}
	screens["titlescreen"] = require("screens.titlescreen")
	screens["playscreen"] = require("screens.playscreen")
	screens["armybuildingscreen"] = require("screens.armybuildingscreen")

	-- Load sounds effects
	soundEffects = {}
	soundEffects["button_click"] = love.audio.newSource("sounds/button_click.wav", "static")
	soundEffects["button_click2"] = love.audio.newSource("sounds/button_click2.wav", "static")

	-- Load fonts
	fonts = {}
	fonts["Romulus"] = love.graphics.newFont("fonts/Romulus.ttf", 48)

	-- Load atlases
	atlas = love.graphics.newImage("sprites/atlas.png")
	atlas:setFilter("linear", "nearest")

	-- Set sprites
	sprites = {}
	sprites["tank"] = {texture = atlas, index = 0}
	sprites["city"] = {texture = atlas, index = 1}

	-- Load title screen
	loadScreen("titlescreen")
end

function love.update(dt)
	traverseAndCall("update", {dt}, screens[currentScreen])
end

function love.draw()
	-- Reset graphics
	love.graphics.reset()
	love.graphics.setBackgroundColor(1, 1, 1)
	love.graphics.setColor(0, 0, 0)

	traverseAndCall("draw", {}, screens[currentScreen])
end

function love.mousepressed(x, y, button, isTouch)
	traverseAndCall("mousepressed", {x, y, button, isTouch}, screens[currentScreen])
end

function love.mousereleased(x, y, button, isTouch)
	traverseAndCall("mousereleased", {x, y, button, isTouch}, screens[currentScreen])
end

function traverseAndCall(method, args, node)
	if node ~= nil then
		if node.children ~= nil then
			for _, child in ipairs(node.children) do
				traverseAndCall(method, args, child)
			end
		end
		if node[method] ~= nil then
			if args[1] ~= nil then
				node[method](unpack(args))
			else
				node[method]()
			end
		end
	end
end

function loadScreen(screen)
	currentScreen = screen
	pcall(screens[currentScreen].load)
end

function toScreenCoordinates(x, y)
	local pos = {}
	pos.x = x + love.graphics.getWidth() / 2.0
	pos.y = -y + love.graphics.getHeight() / 2.0
	return pos
end

function drawRectangle(mode, x, y, width, height)
	local pos = toScreenCoordinates(x, y)
	love.graphics.rectangle(mode, pos.x - width / 2.0, pos.y - height / 2.0, width, height)
end

function drawCircle(mode, x, y, radius)
	local pos = toScreenCoordinates(x, y)
	love.graphics.circle(mode, pos.x, pos.y, radius)
end

function drawText(font, text, x, y)
	local pos = toScreenCoordinates(x, y)
	local text = love.graphics.newText(font, text)
	love.graphics.draw(text, math.floor(pos.x - text:getWidth() / 2.0), math.floor(pos.y - text:getHeight() / 2.0))
end

function drawLine(x, y, x2, y2)
	local pos1 = toScreenCoordinates(x, y)
	local pos2 = toScreenCoordinates(x2, y2)
	love.graphics.line(pos1.x, pos1.y, pos2.x, pos2.y)
end

function drawSprite(spriteName, x, y, width, height)
	local sprite = sprites[spriteName]
	local spriteSize = 32
	local cols = math.ceil(sprite.texture:getWidth() / spriteSize)
	local rows = math.ceil(sprite.texture:getHeight() / spriteSize)
	local clipX = (sprite.index % cols) * spriteSize
	local clipY = (sprite.index % rows) * spriteSize
	local quad = love.graphics.newQuad(clipX, clipY, spriteSize, spriteSize, sprite.texture:getWidth(), sprite.texture:getHeight())
	local pos = toScreenCoordinates(x, y)
	local scale = {x = width / spriteSize, y = height / spriteSize}
	love.graphics.draw(sprite.texture, quad, pos.x - (scale.x * spriteSize) / 2.0, pos.y - (scale.y * spriteSize) / 2.0, 0, scale.x, scale.y)
end

function distanceBetween(x, y, x2, y2)
	return math.sqrt((x - x2)^2 + (y - y2)^2)
end
