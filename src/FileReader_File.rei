type t = FileReader_Types.file;

include (module type of
  FileReader_BlobLike.Make({
    type nonrec t = t;
  }));

let name: t => string;
let lastModified: t => float;

let asBlob: t => FileReader_Blob.t;

let make:
  (
    array(FileReader_BlobPart.t),
    string,
    ~type_: string=?,
    ~lastModified: float=?,
    unit
  ) =>
  t;