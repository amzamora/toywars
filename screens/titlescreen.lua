local screen = {}
screen.callbacks = {}

local ui = require("ui.ui")
local nodes

function screen.load()
	nodes = {}
	table.insert(nodes, ui.Button(0, 0, 180, 80, "PLAY", function()
			loadScreen("armybuildingscreen")
		end))
	table.insert(nodes, ui.Button(0, -110, 180, 80,"QUIT"))
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
