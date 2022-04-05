const Game = @import("game.zig").Game;

pub fn main() !void {
    var game = try Game.init();
    defer game.deinit();

    game.run();
}
