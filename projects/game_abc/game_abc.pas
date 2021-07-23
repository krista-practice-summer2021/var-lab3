(*
 * Project: pascal-sample-game
 * User: user
 * Date: 11/9/18
 *)
program pascalsamplegame;
//FPC Only
{$MODE OBJFPC}

// Закомментировать для Pascal ABC. Раскомментировать для Free Pascal.
// Uses SysUtils;

const
  NO_MANS_TEAM_ID = -1; // Значение признака не занятой ни одним игроком планеты

(* Планета.*)
type
  Planet = class
    private id, ownerTeam, population, reproduction: Integer;
    public
    constructor Create(i, ot, p, r: Integer); //Конструктор
    function getId(): Integer; //Идентификатор планеты
    function getOwnerTeam(): Integer; //Идентификатор игрока
    function getPopulation(): Integer; //Население
    function getReproduction(): Integer; //Прирост
    procedure print(); //Отладочная печать
    procedure setPopulation(p :Integer); //Установить значение населения
    end;

    (* Перемещающаяся группа. *)
type MovingGroup = class
  private ownerTeam, pFrom, pTo, count, stepsLeft : Integer;
  public
    constructor Create(ot, pf, pt, c, sl: Integer); //Конструктор
    function getOwnerTeam(): Integer; //Идентификатор игрока
    function getFrom(): Integer; //С
    function getTo(): Integer; //На
    function getCount(): Integer; //Количество
    function getStepsLeft(): Integer; //Осталось шагов
    procedure debugPrint(); //Отладочная печать
    procedure print(); //Печать
  end;
  
type MovingGroupArray = array of MovingGroup;
type PlanetArray = array of Planet;

type
  Round = record
    teamId: integer; //Идентификатор игрока
    maxSteps: integer; //Максимальное количество ходов
    currentStep: integer; //Текущий шаг
    planetCount: integer; //Количество планет
    distMapSizeIndex: integer;  //Индекс размера таблицы расстояний
    movingGroupsCountIndex: integer; //Индекс количества перемещающихся групп
    movingGroupsCount: integer; //Количество перемещающихся групп
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

// Получить Идентификатор противника по идентификатору игрока.
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

//Отладочная печать
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

// Читает одно целое число из стандартного потока ввода.
function readInt(): integer;
var
   number: integer;
begin
   read(number);
   readInt := number;
end;

//Чтение данных из консоли
function getRoundInternal(): Round;
var
  i, j: integer;
  counter1: integer;
  id, population,ownerTeam,reproduction: integer;
  pFrom, pTo, count, stepsLeft: integer;
begin
  // Считываем ID нашей команды, максимальное количество ходов, текущий ход.
  myRound.teamId := readInt();
  myRound.maxSteps := readInt();
  myRound.currentStep := readInt();
  // Считываем планеты
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
  // Cчитываем таблицу расстояний
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
  // Cчитываем перемещающиеся группы.
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
  // Рассчитываем дополнительные поля.

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

function getRound(): Round;
begin
//*****************************************************************************
//
//Для того, что бы осуществить чтение из файла 123.txt, нужно раскомментировать
//три строчки assign,reset и close
//
//!!! Внимание !!!
//Чтение из файла можно использовать только для отладки вашего приложения
//Перед отправкой его на сервер нужно закоментировать чтение из файла
//
//*****************************************************************************

//    assign(input,'123.txt');
//    reset(input);
    
    getRound := getRoundInternal();
    
//    close(input);
end;

//Выполнить ход
function MakeAMove() : MovingGroupArray;
var required : Integer = 0;
var counter1, counter2: integer;
var mg : MovingGroup;
var move: MovingGroupArray;

begin
  getRound();
  SetLength(move, 0);

  // Место для Вашего кода.

  MakeAMove := move;
end;


//Main procedure
begin
  printMovingGroups(MakeAMove());
end.
