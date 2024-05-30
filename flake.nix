{
  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs @ {flake-parts, ...}:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = ["x86_64-linux" "aarch64-linux" "aarch64-darwin" "x86_64-darwin"];
      perSystem = {
        config,
        self',
        inputs',
        pkgs,
        system,
        ...
      }: {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "plugin-torture";
          version = "0";
          src = ./.;

          nativeBuildInputs = with pkgs; [
            cmake
            pkg-config
          ];

          buildInputs = with pkgs; [
            alsa-lib
            fmt
            freetype
            libGL
            libffi
            libjack2
            libxkbcommon
            lilv
            lv2
            serd
            wayland
            wayland-scanner
            xorg.libX11
            xorg.libXcursor
            xorg.libXi
            xorg.libXinerama
            xorg.libXrandr
          ];
        };

        devShells.default = pkgs.mkShell {
          inputsFrom = [self'.packages.default];
        };
      };
    };
}
