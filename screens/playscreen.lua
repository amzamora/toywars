local screen = {}
screen.callbacks = {}

local image

function screen.load()
	image = love.graphics.newImage("sprites/atlas.png")
	image:setFilter("linear", "nearest")
end

function screen.update(dt)
end

function screen.draw()
	love.graphics.setColor(1, 1, 1, 1)
	-- local quad = love.graphics.newQuad(0, 32, 32, 32, image:getWidth(), image:getHeight())
	-- love.graphics.draw(image, quad, love.graphics.getWidth() / 2.0 - (4 * image:getWidth()) / 2.0, love.graphics.getHeight() / 2.0 - image:getHeight() / 2.0, 0.0, 4, 4)

	love.graphics.draw(image, love.graphics.getWidth() / 2.0 - (4 * image:getWidth()) / 2.0, love.graphics.getHeight() / 2.0 - (2*image:getHeight()) / 2.0, 0.0, 2, 2)
end

return screen
