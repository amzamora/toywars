local screen = {}

local image
local camera
local x
local y

function screen.load()
	image = love.graphics.newImage("sprites/atlas.png")
	image:setFilter("linear", "nearest")

	local cameraFile = require("lib/hump/camera")
	camera = cameraFile()

	x = love.graphics.getWidth() / 2.0
	y = love.graphics.getHeight() / 2.0
end

function screen.update(dt)
	if love.keyboard.isDown("left") then
		x = x - 10
	end
	if love.keyboard.isDown("right") then
		x = x + 10
	end
	if love.keyboard.isDown("up") then
		y = y - 10
	end
	if love.keyboard.isDown("down") then
		y = y + 10
	end
	camera:lookAt(x, y)
end

function screen.draw()
	camera:attach()
		love.graphics.setColor(1, 1, 1, 1)
		-- local quad = love.graphics.newQuad(0, 32, 32, 32, image:getWidth(), image:getHeight())
		-- love.graphics.draw(image, quad, love.graphics.getWidth() / 2.0 - (4 * image:getWidth()) / 2.0, love.graphics.getHeight() / 2.0 - image:getHeight() / 2.0, 0.0, 4, 4)

		love.graphics.draw(image, love.graphics.getWidth() / 2.0 - (4 * image:getWidth()) / 2.0, love.graphics.getHeight() / 2.0 - (2*image:getHeight()) / 2.0, 0.0, 2, 2)
	camera:detach()
end

return screen
