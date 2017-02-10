require 'ffi'

module Raycaster
  extend FFI::Library
  ffi_lib "./raycaster.so"
  attach_function :main, [:int, :pointer], :int
end
