{
  description = "A Nix-flake-based C/C++ development environment";

  inputs.nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1";

  outputs = inputs:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forEachSupportedSystem = f: inputs.nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import inputs.nixpkgs { inherit system; };
      });
    in
    {
      devShells = forEachSupportedSystem ({ pkgs }: {
        default = pkgs.mkShell.override
          {
            # Override stdenv in order to change compiler:
            # stdenv = pkgs.clangStdenv;
          }
          {
            packages = with pkgs; [
              clang-tools
              cmake

              sdl3
              pkg-config

              alsa-lib
              hidapi
              ibus
              jack2
              libdecor
              libGL
              libpulseaudio
              libusb1

              fribidi
              libunwind

              dbus
              liburing
              xorg.libX11
              xorg.libXi
              xorg.libXcursor # libxcursor
              xorg.libXext # libxext
              xorg.libXfixes
              xorg.libXinerama # libxinerama
              xorg.libXrandr # libxrandr
              xorg.libXrender # libxrender
              xorg.libXtst # libxtst
              libxkbcommon

              mesa
              libdrm
              libgbm

              ninja
              pipewire
              sndio
              amdvlk # vulkan-driver
              egl-wayland
              vulkan-headers
              vulkan-loader
              xwayland
              wayland
              wayland-protocols
              wayland-scanner
            ] ++ (if system == "aarch64-darwin" then [ ] else [ gdb ]);
          };
      });
    };
}

