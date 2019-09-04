type t = FileReader_Types.blob;

include (module type of
  FileReader_BlobLike.Make({
    type nonrec t = t;
  }));

let asFile: t => option(FileReader_Types.file);

module Options: {
  type t;

  [@bs.obj]
  external make: (~_type: string=?, ~endings: string=?, unit) => t = "";
};

let make: array(FileReader_BlobPart.t) => t;

let make2: (array(FileReader_BlobPart.t), Options.t) => t;