const sf = struct {
    usingnamespace @import("sfml");
    usingnamespace sf.graphics;
};

pub const Game = struct {
    window: sf.RenderWindow,

    pub fn init() !Game {
        return Game{ .window = try sf.RenderWindow.createDefault(.{ .x = 770, .y = 480 }, "Stuge") };
    }

    pub fn deinit(self: *Game) void {
        self.window.destroy();
    }

    pub fn run(self: *Game) void {
        while (self.window.isOpen()) {
            while (self.window.pollEvent()) |event| {
                if (event == .closed) {
                    self.window.close();
                }
            }
        }
    }
};
