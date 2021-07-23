(*
 * Project: pascal-sample-game
 * User: user
 * Encoding: Cyrillic Windows 866
 *)
program pascalsamplegame;
//FPC Only
{$MODE OBJFPC}

// ���������஢��� ��� Pascal ABC. ��᪮�����஢��� ��� Free Pascal.
Uses SysUtils;

const
  NO_MANS_TEAM_ID = -1; // ���祭�� �ਧ���� �� ����⮩ �� ����� ��ப�� �������

(* ������.*)
type
  Planet = class
    private id, ownerTeam, population, reproduction: Integer;
    public
    constructor Create(i, ot, p, r: Integer); //���������
    function getId(): Integer; //�����䨪��� �������
    function getOwnerTeam(): Integer; //�����䨪��� ��ப�
    function getPopulation(): Integer; //��ᥫ����
    function getReproduction(): Integer; //�����
    procedure print(); //�⫠��筠� �����
    procedure setPopulation(p :Integer); //��⠭����� ���祭�� ��ᥫ����
    end;

    (* ��६������� ��㯯�. *)
type MovingGroup = class
  private ownerTeam, pFrom, pTo, count, stepsLeft : Integer;
  public
    constructor Create(ot, pf, pt, c, sl: Integer); //���������
    function getOwnerTeam(): Integer; //�����䨪��� ��ப�
    function getFrom(): Integer; //�
    function getTo(): Integer; //��
    function getCount(): Integer; //������⢮
    function getStepsLeft(): Integer; //��⠫��� 蠣��
    procedure debugPrint(); //�⫠��筠� �����
    procedure print(); //�����
  end;
  
type MovingGroupArray = array of MovingGroup;
type PlanetArray = array of Planet;

type
  Round = record
    teamId: integer; //�����䨪��� ��ப�
    maxSteps: integer; //���ᨬ��쭮� ������⢮ 室��
    currentStep: integer; //����騩 蠣
    planetCount: integer; //������⢮ ������
    distMapSizeIndex: integer;  //������ ࠧ��� ⠡���� ����ﭨ�
    movingGroupsCountIndex: integer; //������ ������⢠ ��६������� ��㯯
    movingGroupsCount: integer; //������⢮ ��६������� ��㯯
    planets: PlanetArray;
    distMap: array of array of integer;
    movingGroups: MovingGroupArray;

    adversaryTeamId: Integer;

    ownPlanets: PlanetArray;
    adversarysPlanets: PlanetArray;
    noMansPlanets: PlanetArray;
    ownGroups: MovingGroupArray;
    adversarysGroups: MovingGroupArray;

    end;

//Implementation
{ Planet }
constructor Planet.Create(i, ot, p, r: Integer);
begin
  id := i;
  population := p;
  ownerTeam := ot;
  reproduction := r;
end;

function Planet.getId(): Integer;
begin
  getId := id;
end;

function Planet.getOwnerTeam(): Integer;
begin
  getOwnerTeam := ownerTeam;
end;

function Planet.getPopulation(): Integer;
begin
  getPopulation := population;
end;

function Planet.getReproduction(): Integer;
begin
  getReproduction := reproduction;
end;

procedure Planet.print();
begin
  WriteLn(IntToStr(getId()) + ' ' + IntToStr(getOwnerTeam()) + ' ' + IntToStr(getPopulation()) + ' ' + IntToStr(getReproduction()));
end;

procedure Planet.setPopulation(p :Integer);
begin
  population := p;
end;

{ MovingGroup }

constructor MovingGroup.Create(ot, pf, pt, c, sl: Integer);
begin
  pFrom := pf;
  pTo := pt;
  count := c;
  stepsLeft := sl;
  ownerTeam := ot;
end;

function MovingGroup.getOwnerTeam(): Integer;
begin
  getOwnerTeam := ownerTeam;
end;

function MovingGroup.getFrom(): Integer;
begin
  getFrom := pFrom;
end;

function MovingGroup.getTo(): Integer;
begin
  getTo := pTo;
end;

function MovingGroup.getCount(): Integer;
begin
  getCount := count;
end;

function MovingGroup.getStepsLeft(): Integer;
begin
  getStepsLeft := stepsLeft;
end;

procedure MovingGroup.debugPrint();
begin
  WriteLn(IntToStr(getOwnerTeam()) + ' ' + IntToStr(getFrom()) + ' ' + IntToStr(getTo()) + ' ' + IntToStr(getCount()) + ' ' + IntToStr(getStepsLeft()));
end;

procedure MovingGroup.print();
begin
  WriteLn(IntToStr(getFrom()) + ' ' + IntToStr(getTo()) + ' ' + IntToStr(getCount()));
end;

procedure printMovingGroups(movingGroups: MovingGroupArray);
var i : integer = 0;
begin
  WriteLn(Length(movingGroups));
  while (i < Length(movingGroups)) do
  begin
    movingGroups[i].print();
    i := i + 1;
  end;
end;

// ������� �����䨪��� ��⨢���� �� �����䨪���� ��ப�.
function getAdversaryTeamId(teamId: integer): integer;
begin
  if(teamId = 1) then
  begin
    getAdversaryTeamId := 0;
  end
  else if (teamId = 0) then
  begin
    getAdversaryTeamId := 1;
  end;
end;

//�⫠��筠� �����
procedure debugRound(myRound : Round);
var
  i : Integer = 0;
  j : Integer = 0;
begin
  WriteLn(IntToStr(myRound.teamId));
  WriteLn(IntToStr(myRound.maxSteps));
  WriteLn(IntToStr(myRound.currentStep));
  WriteLn(IntToStr(myRound.planetCount));
  while (i < myRound.planetCount) do
  begin
    myRound.planets[i].print();
    i := i + 1;
  end;
  WriteLn(IntToStr(myRound.planetCount));
  for i := 0 to myRound.planetCount-1 do
  begin
    for j := 0 to myRound.planetCount-1 do
    begin
      Write(IntToStr(myRound.distMap[i, j]) + ' ');
    end;
    WriteLn();
  end;
  WriteLn(IntToStr(myRound.movingGroupsCount));
  i := 0;
  while (i < myRound.movingGroupsCount) do
  begin
    myRound.movingGroups[i].debugPrint();
    i := i + 1;
  end;
  WriteLn('Adversary ID ' + IntToStr(getAdversaryTeamId(myRound.teamId)));
  i := 0;
  WriteLn('Own planets ' + IntToStr(Length(myRound.ownPlanets)));
  while (i < Length(myRound.ownPlanets)) do
  begin
    myRound.ownPlanets[i].print();
    i := i + 1;
  end;

  i := 0;
  WriteLn('Adversary planets ' + IntToStr(Length(myRound.adversarysPlanets)));
  while (i < Length(myRound.adversarysPlanets)) do
  begin
    myRound.adversarysPlanets[i].print();
    i := i + 1;
  end;

  i := 0;
  WriteLn('No mans planets ' + IntToStr(Length(myRound.noMansPlanets)));
  while (i < Length(myRound.noMansPlanets)) do
  begin
    myRound.noMansPlanets[i].print();
    i := i + 1;
  end;

  i := 0;
  WriteLn('Own groups ' + IntToStr(Length(myRound.ownGroups)));
  while (i < Length(myRound.ownGroups)) do
  begin
    myRound.ownGroups[i].debugPrint();
    i := i + 1;
  end;

  i := 0;
  WriteLn('Adversary groups ' + IntToStr(Length(myRound.adversarysGroups)));
  while (i < Length(myRound.adversarysGroups)) do
  begin
    myRound.adversarysGroups[i].debugPrint();
    i := i + 1;
  end;

end;

//Globals
var myRound: Round;

// ��⠥� ���� 楫�� �᫮ �� �⠭���⭮�� ��⮪� �����.
function readInt(): integer;
var
   number: integer;
begin
   read(number);
   readInt := number;
end;

//�⥭�� ������ �� ���᮫�
function getRoundInternal(): Round;
var
  i, j: integer;
  counter1: integer;
  id, population,ownerTeam,reproduction: integer;
  pFrom, pTo, count, stepsLeft: integer;
begin
  // ���뢠�� ID ��襩 �������, ���ᨬ��쭮� ������⢮ 室��, ⥪�騩 室.
  myRound.teamId := readInt();
  myRound.maxSteps := readInt();
  myRound.currentStep := readInt();
  // ���뢠�� �������
  myRound.planetCount := readInt();
  SetLength(myRound.planets, myRound.planetCount);
  for i := 0 to myRound.planetCount - 1 do
  begin
	  id := readInt();
	  ownerTeam := readInt();
	  population := readInt();
	  reproduction := readInt();
      myRound.planets[i] := Planet.Create(id,ownerTeam,population,reproduction);
  end;
  // C��뢠�� ⠡���� ����ﭨ�
  myRound.planetCount := readInt();
  SetLength(myRound.distMap, myRound.planetCount);
  for i := 0 to myRound.planetCount - 1 do
  begin
      SetLength(myRound.distMap[i], myRound.planetCount);
      for j := 0 to myRound.planetCount - 1 do
      begin
          myRound.distMap[i, j] := readInt(); 
      end;
  end;
  // C��뢠�� ��६���騥�� ��㯯�.
  myRound.movingGroupsCount := readInt();
  SetLength(myRound.movingGroups, myRound.movingGroupsCount);
  for i := 0 to myRound.movingGroupsCount - 1 do
  begin
	  ownerTeam := readInt();
	  pFrom := readInt(); 
	  pTo := readInt();
	  count := readInt();
	  stepsLeft := readInt();
      myRound.movingGroups[i] := MovingGroup.Create(ownerTeam, pFrom, pTo, count, stepsLeft);
  end;
  // ������뢠�� �������⥫�� ����.

  myRound.adversaryTeamId := getAdversaryTeamId(myRound.teamId);
  counter1 := 0;
  while (counter1 < myRound.planetCount) do
  begin
    if(myRound.planets[counter1].getOwnerTeam() = myRound.teamId) then
    begin
      SetLength(myRound.ownPlanets, Length(myRound.ownPlanets) + 1);
      myRound.ownPlanets[Length(myRound.ownPlanets)-1] := myRound.planets[counter1];
    end;
    if(myRound.planets[counter1].getOwnerTeam() = myRound.adversaryTeamId) then
    begin
      SetLength(myRound.adversarysPlanets, Length(myRound.adversarysPlanets) + 1);
      myRound.adversarysPlanets[Length(myRound.adversarysPlanets)-1] := myRound.planets[counter1];
    end;
    if(myRound.planets[counter1].getOwnerTeam() = NO_MANS_TEAM_ID) then
    begin
      SetLength(myRound.noMansPlanets, Length(myRound.noMansPlanets) + 1);
      myRound.noMansPlanets[Length(myRound.noMansPlanets)-1] := myRound.planets[counter1];
    end;
    counter1 := counter1 + 1;
  end;

  counter1 := 0;
  while (counter1 < myRound.movingGroupsCount) do
  begin
    if(myRound.movingGroups[counter1].getOwnerTeam() = myRound.teamId) then
    begin
      SetLength(myRound.ownGroups, Length(myRound.ownGroups) + 1);
      myRound.ownGroups[Length(myRound.ownGroups)-1] := myRound.movingGroups[counter1];
    end;
    if(myRound.movingGroups[counter1].getOwnerTeam() = myRound.adversaryTeamId) then
    begin
      SetLength(myRound.adversarysGroups, Length(myRound.adversarysGroups) + 1);
      myRound.adversarysGroups[Length(myRound.adversarysGroups)-1] := myRound.movingGroups[counter1];
    end;
    counter1 := counter1 + 1;
  end;

  getRoundInternal := myRound;
end;

//�믮����� 室
function MakeAMove() : MovingGroupArray;
var required : Integer = 0;
var counter1, counter2: integer;
var mg : MovingGroup;
var move: MovingGroupArray;

begin
  getRoundInternal();
  SetLength(move,0);

  // ���� ��� ��襣� ����

  MakeAMove := move;
end;


//Main procedure
begin
  printMovingGroups(MakeAMove());
end.
