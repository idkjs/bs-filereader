type blob;
type file;

let isArrayBuffer: Js.Json.t => bool = [%raw
  {|
    function(value) {
        return value instanceof ArrayBuffer;
    }
|}
];

external asArrayBufferUnsafe: Js.Json.t => Js.Typed_array.ArrayBuffer.t =
  "%identity";

let asArrayBuffer = x =>
  if (x->isArrayBuffer) {
    Some(asArrayBufferUnsafe(x));
  } else {
    None;
  };

external asBlobUnsafe: Js.Json.t => blob = "%identity";

let isBlob: Js.Json.t => bool = [%raw
  {|
  function(value) {
    return value instanceof Blob;
  }
  |}
];

let asBlob = x =>
  if (x->isBlob) {
    Some(x->asBlobUnsafe);
  } else {
    None;
  };