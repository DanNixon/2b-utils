#include <cli/cli.h>
#include <cli/clilocalsession.h>
#include <cli/remotecli.h>
#include <spdlog/spdlog.h>

#include "2b/powerbox_serial.hpp"

int main()
{
  spdlog::set_level(spdlog::level::info);

  /* Init powerbox */
  /* TODO: make port configurable */
  estim2b::PowerboxSerial powerbox("/dev/ttyUSB0");

  /* Build menu */
  auto menu = std::make_unique<cli::Menu>("2bctl");

  menu->Insert("status",
               [&](std::ostream &out) {
                 try
                 {
                   auto const s = powerbox.status();
                   out << "Status: " << s << '\n';
                 }
                 catch (std::runtime_error const &e)
                 {
                   out << "Error: " << e.what() << '\n';
                 }
               },
               "Query status from the powerbox.");

  menu->Insert("reset",
               [&](std::ostream &out) {
                 try
                 {
                   powerbox.reset();
                   auto const s = powerbox.status(true);
                   out << "Status: " << s << '\n';
                 }
                 catch (std::runtime_error const &e)
                 {
                   out << "Error: " << e.what() << '\n';
                 }
               },
               "Reset the powerbox.");

  menu->Insert("kill",
               [&](std::ostream &out) {
                 try
                 {
                   powerbox.kill();
                   auto const s = powerbox.status(true);
                   out << "Status: " << s << '\n';
                 }
                 catch (std::runtime_error const &e)
                 {
                   out << "Error: " << e.what() << '\n';
                 }
               },
               "Turn off all outputs.");

  menu->Insert("staged",
               [&](std::ostream &out) {
                 auto const s = powerbox.staged_settings();
                 out << "Staged: " << s << '\n';
               },
               "View staged settings.");

  menu->Insert("rollback",
               [&](std::ostream &out) {
                 powerbox.rollback();
                 auto const s = powerbox.staged_settings();
                 out << "Staged: " << s << '\n';
               },
               "Rollback (unstage/reset) staged settings.");

  menu->Insert("commit",
               [&](std::ostream &out) {
                 try
                 {
                   powerbox.commit();
                   auto const s = powerbox.status(true);
                   out << "Status: " << s << '\n';
                 }
                 catch (std::runtime_error const &e)
                 {
                   out << "Error: " << e.what() << '\n';
                 }
               },
               "Commits (applies) stages settings to powerbox.");

  menu->Insert("low",
               [&](std::ostream &out) {
                 powerbox.set_power_level(estim2b::PowerLevel::Low);
                 auto const s = powerbox.staged_settings();
                 out << "Staged: " << s << '\n';
               },
               "Set power level to low.");

  menu->Insert("high",
               [&](std::ostream &out) {
                 powerbox.set_power_level(estim2b::PowerLevel::High);
                 auto const s = powerbox.staged_settings();
                 out << "Staged: " << s << '\n';
               },
               "Set power level to high.");

  menu->Insert("link",
               [&](std::ostream &out) {
                 powerbox.set_channel_link(estim2b::ChannelLink::Linked);
                 auto const s = powerbox.staged_settings();
                 out << "Staged: " << s << '\n';
               },
               "Link output channel intensity controls.");

  menu->Insert("unlink",
               [&](std::ostream &out) {
                 powerbox.set_channel_link(estim2b::ChannelLink::Independant);
                 auto const s = powerbox.staged_settings();
                 out << "Staged: " << s << '\n';
               },
               "Unlink output channel intensity controls.");

  menu->Insert("mode", {"name"},
               [&](std::ostream &out, std::string const &mode) {
                 try
                 {
                   powerbox.set_mode(mode);
                   auto const s = powerbox.staged_settings();
                   out << "Staged: " << s << '\n';
                 }
                 catch (std::runtime_error const &e)
                 {
                   out << "Error: " << e.what() << '\n';
                 }
               },
               "Set pattern mode.");

  menu->Insert(
      "channel", {"channel", "value"},
      [&](std::ostream &out, std::string const &channel, int const value) {
        try
        {
          powerbox.set_channel_intensity(channel, value);
          auto const s = powerbox.staged_settings();
          out << "Staged: " << s << '\n';
        }
        catch (std::runtime_error const &e)
        {
          out << "Error: " << e.what() << '\n';
        }
      },
      "Set channel output intensity.");

  menu->Insert(
      "adjust", {"parameter", "value"},
      [&](std::ostream &out, std::string const &adjustment, int const value) {
        try
        {
          powerbox.set_adjustment(adjustment, value);
          auto const s = powerbox.staged_settings();
          out << "Staged: " << s << '\n';
        }
        catch (std::runtime_error const &e)
        {
          out << "Error: " << e.what() << '\n';
        }
      },
      "Set feeling adjustment parameters.");

  /* Create CLI */
  cli::Cli cli(std::move(menu));
  cli::SetColor();

  boost::asio::io_service io;

  /* Local CLI */
  cli::CliLocalSession session(cli, io, std::cout);
  session.ExitAction([&io](auto &out) { io.stop(); });

  /* Remote CLI */
  cli::CliTelnetServer server(io, 5000, cli);

  io.run();

  powerbox.close_connection();

  return 0;
}
