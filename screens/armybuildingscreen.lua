local screen = {}
screen.children = {}

local ui = require("ui.ui")

function screen.load()
	image = love.graphics.newImage("sprites/atlas.png")
	image:setFilter("linear", "nearest")

	screen.children = {}
	table.insert(screen.children, ui.makeCard(screen, -100, 0, "tank"))
end

function screen.update(dt)
end

function screen.draw()
end

return screen
