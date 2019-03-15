type t = [
  | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)
  | `Int8Array(Js.Typed_array.Int8Array.t)
  | `Uint8Array(Js.Typed_array.Uint8Array.t)
  | `Uint8ClampedArray(Js.Typed_array.Uint8ClampedArray.t)
  | `Int16Array(Js.Typed_array.Int16Array.t)
  | `Uint16Array(Js.Typed_array.Uint16Array.t)
  | `Int32Array(Js.Typed_array.Int32Array.t)
  | `Uint32Array(Js.Typed_array.Uint32Array.t)
  | `Float32Array(Js.Typed_array.Float32Array.t)
  | `Float64Array(Js.Typed_array.Float64Array.t)
  | `DataView(Js.Typed_array.DataView.t)
  | `Blob(FileReader__.blob)
  | `String(string)
];

let toJson: t => Js.Json.t;