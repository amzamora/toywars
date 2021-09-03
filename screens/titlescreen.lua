local screen = {}
screen.callbacks = {}

local ui = require("ui.ui")
local nodes = {}
table.insert(nodes, ui.makeButton(
	love.graphics.getWidth() / 2.0,
	love.graphics.getHeight() / 2.0,
	180, 80,
	"PLAY",
	function()
		loadScreen("playscreen")
	end)
)
table.insert(nodes, ui.makeButton(
	love.graphics.getWidth() / 2.0,
	love.graphics.getHeight() / 2.0 + 110,
	180,
	80,
	"QUIT")
)

function screen.load()
end

function screen.update(dt)

end

function screen.draw()
	for _, button in ipairs(nodes) do
		button.draw()
	end
end

function screen.mousepressed(x, y, mouseButton, istouch, presses)
	for _, button in ipairs(nodes) do
		button.mousepressed(x, y, mouseButton, istouch, presses)
	end
end

function screen.mousereleased(x, y, mouseButton, istouch)
	for _, button in ipairs(nodes) do
		button.mousereleased(x, y, mouseButton, istouch)
	end
end

return screen
