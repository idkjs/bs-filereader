open FileReader__;

type t = blob;

include FileReader_BlobLike.Make({
  type nonrec t = t;
});

let asFile: t => option(file) = [%raw
  {|
function(blob) {
  if (blob instanceof File) {
    return blob;
  }
}
|}
];

module Options = {
  type t;

  [@bs.obj]
  external make: (~_type: string=?, ~endings: string=?, unit) => t = "";
};

[@bs.new] external make: array(FileReader_BlobPart.t) => t = "Blob";

[@bs.new]
external makeWithOptions: (array(FileReader_BlobPart.t), Options.t) => t =
  "Blob";