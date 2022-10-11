cv :: Mat faceEncodings ( const std :: vector < cv :: Mat > & images ) {
  cv :: Mat img = cv :: Mat :: zeros ( images . size ( ), CV_8UC1 );
  cv :: Mat :: Ptr faceEncodings = cv :: Mat :: zeros ( images . size ( ), CV_8UC1 );
  cv :: Mat :: Ptr personNames = cv :: Mat :: zeros ( images . size ( ), CV_8UC1 );
  std :: vector < cv :: Mat > myList = images;
  std :: cout << myList << std :: endl;
  for ( const auto & cu_img : myList ) {
    cv :: Mat current_Img = cv :: imread ( f "{path}/{cu_img}" );
    images . push_back ( current_Img );
    personNames -> push_back ( cv :: imread ( cu_img ) );
  }
  std :: cout << personNames << std :: endl;
  typedef std :: vector < cv :: Mat > faceEncodings;
  faceEncodings encodeList;
  for ( const auto & img : images ) {
    cv :: Mat img = cv :: cvtColor ( img, img, cv :: COLOR_BGR2RGB );
    faceEncodings encode = faceEncodings :: faceEncodings ( img ) . at < faceEncodings :: FaceEncoding > ( );
    encodeList . push_back ( encode );
  }
  return encodeList;
  ;
}

void attendance ( string name ) {
  std :: ifstream file ( "Attendance.csv", "r+" );
  if ( ! file ) return;
  std :: vector < std :: string > myDataList;
  file >> myDataList;
  std :: vector < string > nameList;
  for ( auto & line : myDataList ) {
    auto entry = line . split ( ',' );
    nameList . push_back ( entry [ 0 ] );
  }
  if ( name != "" ) {
    auto time_now = std :: chrono :: high_resolution_clock :: now ( );
    auto tStr = time_now . time_since_epoch ( );
    auto dStr = time_now . time_since_epoch ( );
    file << f "\n{name},{tStr},{dStr}";
  }
  auto encodeListKnown = faceEncodings ( images );
  cout << "All Encodings Complete!!!" << endl;
  cv :: VideoCapture cap ( 1 );
  while ( true ) {
    int ret, frame;
    cap >> ret;
    cv :: Mat faces;
    cv :: resize ( frame, ( int ) ( ret / 2 ), NULL, 0.25, 0.25 );
    faces = cv :: cvtColor ( faces, faces, cv :: COLOR_BGR2RGB );
    auto facesCurrentFrame = face_recognition :: face_locations ( faces );
    auto encodesCurrentFrame = face_recognition :: face_encodings ( faces, facesCurrentFrame );
    for ( auto encodeFace : encodesCurrentFrame ) {
      auto matches = face_recognition :: compare_faces ( encodeListKnown, encodeFace );
      auto faceDis = face_recognition :: face_distance ( encodeListKnown, encodeFace );
      auto matchIndex = std :: distance ( faceDis, matches . begin ( ) );
      if ( matches [ matchIndex ] ) {
        string name = personNames [ matchIndex ] . c_str ( );
        int y1, x2, y2, x1;
        y1 = faceLoc [ matchIndex ];
        x2 = y1 * 4;
        y2 = x2 * 4;
        x1 = y1 * 4;
        cv :: rectangle ( frame, ( int ) ( x1, y1 ), ( int ) ( x2, y2 ), ( int ) ( 0, 255, 0 ), 2 );
        cv :: rectangle ( frame, ( int ) ( x1, y2 - 35 ), ( int ) ( x2, y2 ), ( int ) ( 0, 255, 0 ), cv :: FILLED );
      }
    }
  }