local screen = {}
screen.callbacks = {}

local ui = require("ui.ui")
local nodes

function screen.load()
	image = love.graphics.newImage("sprites/atlas.png")
	image:setFilter("linear", "nearest")

	nodes = {}
	table.insert(nodes, ui.makeCard(120, love.graphics.getHeight() / 2.0, "tank"))
end

function screen.update(dt)
	for _, node in ipairs(nodes) do
		node.update(dt)
	end
end

function screen.draw()
	for i, node in ipairs(nodes) do
		node.draw()
	end
end

return screen
